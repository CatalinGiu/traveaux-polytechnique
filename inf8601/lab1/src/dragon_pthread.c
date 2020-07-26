/*
 * dragon_pthread.c
 *
 *  Created on: 2011-08-17
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <pthread.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "utils.h"
#include "dragon.h"
#include "color.h"
#include "dragon_pthread.h"

#define PRINT_PTHREAD_ERROR(err, msg) \
	do { errno = err; perror(msg); } while(0)

pthread_mutex_t mutex_stdout;

void printf_threadsafe(char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	pthread_mutex_lock(&mutex_stdout);
	vprintf(format, ap);
	pthread_mutex_unlock(&mutex_stdout);
	va_end(ap);
}

/**
 * Does the work on a part of the dragon.
 * Returns 0 on success.
 */
void* dragon_draw_worker(void *data)
{
	/* 1. Initialiser la surface */
	struct draw_data *info = (struct draw_data*) data;

	// assuming area is perfectly divisible by nb_threads
	int area_step_size = info->dragon_width * info->dragon_height / info->nb_thread;
	init_canvas(info->id * area_step_size, (info->id + 1) * area_step_size, info->dragon, -1);

	int ret = pthread_barrier_wait(info->barrier);
	if (ret < 0 && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
		printf_threadsafe("pthread_barrier_wait (%ld)", info->id);
		pthread_exit((void*)-1);
	}

	/* 2. Dessiner les dragons dans les 4 directions
	 *
	 * Il est attendu que chaque threads dessine une partie
	 * de chaque dragon.
	 * */
	
	uint64_t start = info->id * info->size / info->nb_thread;
	uint64_t end;
	if(info->id != NB_TILES - 1){
		end = (info->id + 1) * info->size / info->nb_thread;
	}else{
		end = info->size;
	}

	for(int j = 0; j < NB_TILES; j++)
		dragon_draw_raw(j, start, end, info->dragon, info->dragon_width, info->dragon_height, info->limits, info->id, fold_directions[j]);
	
	
	ret = pthread_barrier_wait(info->barrier);
	if (ret < 0 && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
		printf_threadsafe("pthread_barrier_wait (%ld)", info->id);
		pthread_exit((void*)-1);
	}

	/* 3. Effectuer le rendu final */
	// assuming area is perfectly divisible by nb_threads
	uint64_t height_step_size = info->image_height / info->nb_thread;
	start = info->id * height_step_size;
	end = (info->id + 1) * height_step_size;
	scale_dragon(
		start, end, 
		info->image, info->image_width, info->image_height, 
		info->dragon, info->dragon_width, info->dragon_height, 
		info->palette);
	return NULL;
}

int dragon_draw_pthread(char **canvas, struct rgb *image, int width, int height, uint64_t size, int nb_thread)
{
	int i;
	pthread_t *threads = NULL;
	pthread_barrier_t barrier;
	limits_t lim;
	struct draw_data info;
	char *dragon = NULL;
	int scale_x;
	int scale_y;
	struct draw_data *data = NULL;
	struct palette *palette = NULL;
	int ret = 0;

	palette = init_palette(nb_thread);
	if (palette == NULL)
		goto err;

	/* 1. Initialiser barrier. */

	if (dragon_limits_pthread(&lim, size, nb_thread) < 0)
		goto err;

	info.dragon_width = lim.maximums.x - lim.minimums.x;
	info.dragon_height = lim.maximums.y - lim.minimums.y;

	if ((dragon = (char *) malloc(info.dragon_width * info.dragon_height)) == NULL) {
		printf("malloc error dragon\n");
		goto err;
	}

	if ((data = malloc(sizeof(struct draw_data) * nb_thread)) == NULL) {
		printf("malloc error data\n");
		goto err;
	}

	if ((threads = malloc(sizeof(pthread_t) * nb_thread)) == NULL) {
		printf("malloc error threads\n");
		goto err;
	}

	info.image_height = height;
	info.image_width = width;
	scale_x = info.dragon_width / width + 1;
	scale_y = info.dragon_height / height + 1;
	info.scale = (scale_x > scale_y ? scale_x : scale_y);
	info.deltaJ = (info.scale * width - info.dragon_width) / 2;
	info.deltaI = (info.scale * height - info.dragon_height) / 2;
	info.nb_thread = nb_thread;
	info.dragon = dragon;
	info.image = image;
	info.size = size;
	info.limits = lim;
	info.barrier = &barrier;
	info.palette = palette;

	if (pthread_barrier_init(&barrier, NULL, nb_thread)){
		printf("Error initialising barrier");
        goto err;
	}

	/* 2. Lancement du calcul parallèle principal avec dragon_draw_worker */

	for (i = 0; i < nb_thread; i++) {
		data[i] = info;
		data[i].id = i;


        ret = pthread_create(&threads[i], NULL, dragon_draw_worker, &data[i]);
        if(ret){
            printf("Error initialising thread #%d", i);
            goto err;
        }
    }
	/* 3. Attendre la fin du traitement */
	for (i = 0; i < nb_thread; i++) {
        ret = pthread_join(threads[i], NULL);
        if(ret){
            printf("Error with the completion of thread #%d", i);
            goto err;
        }
    }

	/* 4. Destruction des variables. */
	if (pthread_barrier_destroy(&barrier) < 0) {
        printf("Error with the destruction of barrier");
        goto err;
    }

done:
	FREE(data);
	FREE(threads);
	free_palette(palette);
	*canvas = dragon;
	// *canvas = NULL; // TODO: retourner le dragon calculé
	return ret;

err:
	FREE(dragon);
	ret = -1;
	goto done;
}

void *dragon_limit_worker(void *data)
{
	int i;
	struct limit_data *lim = (struct limit_data *) data;
	int start = lim->start;
	int end = lim->end;

	for (i = 0; i < NB_TILES; i++) {
		piece_limit(start, end, &lim->pieces[i]);
	}

	return NULL;
}

/*
 * Calcule les limites en terme de largeur et de hauteur de
 * la forme du dragon. Requis pour allouer la matrice de dessin.
 */
int dragon_limits_pthread(limits_t *limits, uint64_t size, int nb_thread)
{
	int ret = 0;
	int i;
	pthread_t *threads = NULL;
	struct limit_data *thread_data = NULL;
	piece_t masters[NB_TILES];

	for (i = 0; i < NB_TILES; i++) {
		/**
		 * La pièce master représente les limites d'un dragon complet.
		 * Notez bien que chaque dragon à une orientation différente.
		 */
		piece_init(&masters[i]);
		masters[i].orientation = tiles_orientation[i];
	}

	/* 1. Allouer de l'espace pour threads et threads_data. */
    threads = malloc(nb_thread * sizeof(pthread_t));
    thread_data = malloc(nb_thread * sizeof(struct limit_data));

    // assuming size is perfectly divisible by nb_thread
    uint64_t step_size = size / nb_thread;
    for (i = 0; i < nb_thread; i++){
        thread_data[i].id = i;
        thread_data[i].start = i * step_size;
		if(i < nb_thread - 1){
        	thread_data[i].end = (i + 1) * step_size;
		} else {
			thread_data[i].end = size;
		}
        memcpy( thread_data[i].pieces, masters, sizeof(masters) );
    }

	/* 2. Lancement du calcul en parallèle avec dragon_limit_worker. */
    for (i = 0; i < nb_thread; i++) {
        ret = pthread_create(&threads[i], NULL, dragon_limit_worker, &thread_data[i]);
        if(ret){
            printf("Error initialising thread #%d", i);
            goto err;
        }
    }
	/* 3. Attendre la fin du traitement. */
    for (i = 0; i < nb_thread; i++) {
        ret = pthread_join(threads[i], NULL);
        if(ret){
            printf("Error with the completion of thread #%d", i);
            goto err;
        }
    }
	/* 4. Fusion des pièces.
	 *
	 * La fonction piece_merge est disponible afin d'accomplir ceci.
	 * Notez bien que les pièces ayant la même orientation initiale
	 * doivent être fusionnées ensemble.
	 * */
    for (i = 0; i < NB_TILES; i++) {
        for( int j = 0; j < nb_thread; j++){
            piece_merge(&masters[i], thread_data[j].pieces[i], tiles_orientation[i]);
        }
    }

	/* La limite globale est calculée à partir des limites
	 * de chaque dragon calculées à l'étape 4.
	 */
    for (i = 1; i < NB_TILES; i++) {
        merge_limits(&masters[0].limits, &masters[i].limits);
    }

done:
	FREE(threads);
	FREE(thread_data);
	*limits = masters[0].limits;
	return ret;
err:
	ret = -1;
	goto done;
}
