/*
 i* dragon_tbb.c
 *
 *  Created on: 2011-08-17
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#include <iostream>

extern "C" {
#include "dragon.h"
#include "color.h"
#include "utils.h"
}
#include "dragon_tbb.h"
#include "tbb/tbb.h"
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"
#include "TidMap.h"

using namespace std;
using namespace tbb;

class DragonLimits {
	public:
	piece_t pieces[NB_TILES];

	DragonLimits(){
		for( int i = 0; i < NB_TILES; i++ ){
			piece_init(&pieces[i]);
			pieces[i].orientation = tiles_orientation[i];
		}
	}

	DragonLimits(DragonLimits& dragonLimits, split) {
		for(int i = 0; i < NB_TILES; i++) {
			piece_init(&pieces[i]);
			pieces[i].orientation = tiles_orientation[i];
		}
	}

	void join(DragonLimits& dragonLimits) {
		for(int i = 0; i < NB_TILES; i++) {
            piece_merge(&pieces[i], dragonLimits.pieces[i], tiles_orientation[i]);
		}
	}

	void operator()( const blocked_range<uint64_t>& range ) {
		for( int i = 0; i < NB_TILES; i++ ){
			piece_limit(range.begin(), range.end(), &pieces[i]);
		}
 	}
};

class DragonDraw {
	private:
	draw_data* _info;

	public:
	DragonDraw(draw_data* info): _info(info){}
	
	void operator()(const blocked_range<uint64_t>& range) const {
		// printf("tid (%d)\n", gettid());
		uint64_t start = range.begin();
		uint64_t end = range.end();
		int id = _info->size / _info->nb_thread;
		if (id != 0){
			id = start / id;
		}
		for(int j = 0; j < NB_TILES; j++){
			dragon_draw_raw(j, start, end, 
			_info->dragon, _info->dragon_width, _info->dragon_height, 
			_info->limits, id, fold_directions[j]);
		}
	}
};

class DragonRender {
	private:
	draw_data* _info;

	public:
	DragonRender(draw_data* info): _info(info){}
	void operator()(const blocked_range<int>& range) const {
		scale_dragon(range.begin(), range.end(), 
		_info->image, _info->image_width, _info->image_height, 
		_info->dragon, _info->dragon_width, _info->dragon_height, 
		_info->palette);
	}
};

class DragonClear {
	private:
	char *_dragon;
	public:
	DragonClear(char *dragon): _dragon(dragon){}

	void operator()(const blocked_range<int>& range) const {
		init_canvas(range.begin(), range.end(), _dragon, -1);
	}
};

int dragon_draw_tbb(char **canvas, struct rgb *image, int width, int height, uint64_t size, int nb_thread)
{
	struct draw_data data;
	limits_t limits;
	char *dragon = NULL;
	int dragon_width;
	int dragon_height;
	int dragon_surface;
	int scale_x;
	int scale_y;
	int scale;
	int deltaJ;
	int deltaI;
	struct palette *palette = init_palette(nb_thread);
	if (palette == NULL)
		return -1;

	/* 1. Calculer les limites du dragon */
	dragon_limits_tbb(&limits, size, nb_thread);

	task_scheduler_init init(nb_thread);
	
	dragon_width = limits.maximums.x - limits.minimums.x;
	dragon_height = limits.maximums.y - limits.minimums.y;
	dragon_surface = dragon_width * dragon_height;
	scale_x = dragon_width / width + 1;
	scale_y = dragon_height / height + 1;
	scale = (scale_x > scale_y ? scale_x : scale_y);
	deltaJ = (scale * width - dragon_width) / 2;
	deltaI = (scale * height - dragon_height) / 2;

	dragon = (char *) malloc(dragon_surface);
	if (dragon == NULL) {
		free_palette(palette);
		return -1;
	}

	data.nb_thread = nb_thread;
	data.dragon = dragon;
	data.image = image;
	data.size = size;
	data.image_height = height;
	data.image_width = width;
	data.dragon_width = dragon_width;
	data.dragon_height = dragon_height;
	data.limits = limits;
	data.scale = scale;
	data.deltaI = deltaI;
	data.deltaJ = deltaJ;
	data.palette = palette;
	data.tid = (int *) calloc(nb_thread, sizeof(int));

	/* 2. Initialiser la surface : DragonClear */
	DragonClear dragonClear(dragon);
	parallel_for(blocked_range<int>(0, dragon_surface), dragonClear);

	/* 3. Dessiner le dragon : DragonDraw */
	DragonDraw dragonDraw(&data);
	parallel_for(blocked_range<uint64_t>(0, size), dragonDraw);

	/* 4. Effectuer le rendu final */
	DragonRender dragonRender(&data);
	parallel_for(blocked_range<int>(0, height), dragonRender);

	free_palette(palette);
	FREE(data.tid);
	*canvas = dragon;
	// *canvas = NULL; // TODO: Retourner le dragon calculé
	return 0;
}

/*
 * Calcule les limites en terme de largeur et de hauteur de
 * la forme du dragon. Requis pour allouer la matrice de dessin.
 */
int dragon_limits_tbb(limits_t *limits, uint64_t size, int nb_thread)
{
	DragonLimits lim;

	/* 1. Calculer les limites */
    task_scheduler_init init(nb_thread);
	parallel_reduce(blocked_range<uint64_t>(0, size), lim);

	/* La limite globale est calculée à partir des limites
	 * de chaque dragon.
	 */
    for (int i = 1; i < NB_TILES; i++) {
        merge_limits(&lim.pieces[0].limits, &lim.pieces[i].limits);
    }

	*limits = lim.pieces[0].limits;
	return 0;
}
