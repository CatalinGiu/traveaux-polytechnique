/*
 * heatsim.c
 *
 *  Created on: 2011-11-17
 *      Author: francis
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

#include "config.h"
#include "part.h"
#include "grid.h"
#include "cart.h"
#include "image.h"
#include "heat.h"
#include "memory.h"
#include "util.h"

#define PROGNAME "heatsim"
#define DEFAULT_OUTPUT_PPM "heatsim.png"
#define DEFAULT_DIMX 1
#define DEFAULT_DIMY 1
#define DEFAULT_ITER 110
#define MAX_TEMP 1000.0
#define DIM_2D 2

/* Each MPI node has its context */
typedef struct ctx {
	/* Array of grids : see cart.h */
	cart2d_t *cart;
	/* Overall grid */
	grid_t *global_grid;
	/* Current sub_grid being worked on */
	grid_t *curr_grid;
	grid_t *next_grid;
	grid_t *heat_grid;
	int numprocs;
	int rank;
	MPI_Comm comm2d;
	FILE *log;
	int verbose;
	int dims[DIM_2D];
	/* Boolean expressing whether the grid wraps around in the x or y direction */
	int isperiodic[DIM_2D];
	int coords[DIM_2D];
	int reorder;
	/* The ranks of the processes located in the different directions */
	int north_peer;
	int south_peer;
	int east_peer;
	int west_peer;
	MPI_Datatype vector;
} ctx_t;

typedef struct command_opts {
	int dimx;
	int dimy;
	int iter;
	char *input;
	char *output;
	int verbose;
} opts_t;

static opts_t *global_opts = NULL;

__attribute__((noreturn))
static void usage(void) {
	fprintf(stderr, PROGNAME " " VERSION " " PACKAGE_NAME "\n");
	fprintf(stderr, "Usage: " PROGNAME " [OPTIONS] [COMMAND]\n");
	fprintf(stderr, "\nOptions:\n");
	fprintf(stderr, "  --help	this help\n");
	fprintf(stderr, "  --iter	number of iterations to perform\n");
	fprintf(stderr, "  --dimx	2d decomposition in x dimension\n");
	fprintf(stderr, "  --dimy	2d decomposition in y dimension\n");
	fprintf(stderr, "  --input  png input file\n");
	fprintf(stderr, "  --output ppm output file\n");
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

static void dump_opts(struct command_opts *opts) {
	printf("%10s %s\n", "option", "value");
	printf("%10s %d\n", "dimx", opts->dimx);
	printf("%10s %d\n", "dimy", opts->dimy);
	printf("%10s %d\n", "iter", opts->iter);
	printf("%10s %s\n", "input", opts->input);
	printf("%10s %s\n", "output", opts->output);
	printf("%10s %d\n", "verbose", opts->verbose);
}

void default_int_value(int *val, int def) {
	if (*val == 0)
		*val = def;
}

static int parse_opts(int argc, char **argv, struct command_opts *opts) {
	int idx;
	int opt;
	int ret = 0;

	struct option options[] = { { "help", 0, 0, 'h' },
			{ "iter", 1, 0, 'r' }, { "dimx", 1, 0, 'x' }, { "dimy",
					1, 0, 'y' }, { "input", 1, 0, 'i' }, {
					"output", 1, 0, 'o' }, { "verbose", 0,
					0, 'v' }, { 0, 0, 0, 0 } };

	memset(opts, 0, sizeof(struct command_opts));

	while ((opt = getopt_long(argc, argv, "hvx:y:l:", options, &idx)) != -1) {
		switch (opt) {
		case 'r':
			opts->iter = atoi(optarg);
			break;
		case 'y':
			opts->dimy = atoi(optarg);
			break;
		case 'x':
			opts->dimx = atoi(optarg);
			break;
		case 'i':
			if (asprintf(&opts->input, "%s", optarg) < 0)
				goto err;
			break;
		case 'o':
			if (asprintf(&opts->output, "%s", optarg) < 0)
				goto err;
			break;
		case 'h':
			usage();
			break;
		case 'v':
			opts->verbose = 1;
			break;
		default:
			printf("unknown option %c\n", opt);
			ret = -1;
			break;
		}
	}

	/* default values*/
	default_int_value(&opts->iter, DEFAULT_ITER);
	default_int_value(&opts->dimx, DEFAULT_DIMX);
	default_int_value(&opts->dimy, DEFAULT_DIMY);
	if (opts->output == NULL)
		if (asprintf(&opts->output, "%s", DEFAULT_OUTPUT_PPM) < 0)
			goto err;
	if (opts->input == NULL) {
		fprintf(stderr, "missing input file");
		goto err;
	}

	if (opts->dimx == 0 || opts->dimy == 0) {
		fprintf(stderr,
				"argument error: dimx and dimy must be greater than 0\n");
		ret = -1;
	}

	if (opts->verbose)
		dump_opts(opts);
	global_opts = opts;
	return ret;
	err:
	FREE(opts->input);
	FREE(opts->output);
	return -1;
}

FILE *open_logfile(int rank) {
	char str[255];
	sprintf(str, "out-%d", rank);
	FILE *f = fopen(str, "w+");
	return f;
}

ctx_t *make_ctx() {
	ctx_t *ctx = (ctx_t *) calloc(1, sizeof(ctx_t));
	return ctx;
}

void free_ctx(ctx_t *ctx) {
	if (ctx == NULL)
		return;
	free_grid(ctx->global_grid);
	free_grid(ctx->curr_grid);
	free_grid(ctx->next_grid);
	free_grid(ctx->heat_grid);
	free_cart2d(ctx->cart);
	if (ctx->log != NULL) {
		fflush(ctx->log);
		fclose(ctx->log);
	}
	FREE(ctx);
}

void dump_ctx(ctx_t *ctx) {
	fprintf(ctx->log, "*** CONTEXT ***\n");
	fprintf(ctx->log, "rank=%d\n", ctx->rank);
	fprintf(ctx->log, "north=%d south=%d west=%d east=%d \n",
			ctx->north_peer, ctx->south_peer,
			ctx->east_peer, ctx->west_peer);
	fprintf(ctx->log, "***************\n");
}

int init_ctx(ctx_t *ctx, opts_t *opts) {
	MPI_Comm_size(MPI_COMM_WORLD, &ctx->numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &ctx->rank);

	if (opts->dimx * opts->dimy != ctx->numprocs) {
		fprintf(stderr,
				"2D decomposition blocks must equal number of process\n");
		goto err;
	}

	ctx->log = open_logfile(ctx->rank);
	ctx->verbose = opts->verbose;
	ctx->dims[0] = opts->dimx;
	ctx->dims[1] = opts->dimy;
	ctx->isperiodic[0] = 1;
	ctx->isperiodic[1] = 1;
	ctx->reorder = 0;
	grid_t *new_grid = NULL;

	/* TODO: Créer un "2D cartesian communicator" */
	MPI_Cart_create(MPI_COMM_WORLD, DIM_2D, ctx->dims, ctx->isperiodic, ctx->reorder, &ctx->comm2d);
	MPI_Cart_shift(ctx->comm2d, 1, 1, &ctx->north_peer, &ctx->south_peer);
	MPI_Cart_shift(ctx->comm2d, 0, 1, &ctx->west_peer, &ctx->east_peer);
	MPI_Cart_coords(ctx->comm2d, ctx->rank, DIM_2D, ctx->coords);

	/*
	 * TODO: Le processus rank=0 charge l'image du disque
	 * et transfert chaque section aux autres processus
	 */

	int width_tag = 0; 
	int height_tag = 1; 
	int padding_tag = 2; 
	int data_tag = 3;
	int n_msgs = 4; 
	

	if (ctx->rank == 0) {
		/* Charger l'image d'entrée */
		image_t *image = load_png(opts->input);
		if (image == NULL)
			goto err;

		/* Initialisation de la grid avec le canal rouge */
		ctx->global_grid = grid_from_image(image, CHAN_RED);

		/* La grid a été normalisée à 1, mutiplication par MAX_TEMP */
		grid_multiply(ctx->global_grid, MAX_TEMP);

		/* Décomposition 2D */
		ctx->cart = make_cart2d(ctx->global_grid->width,
				ctx->global_grid->height, opts->dimx, opts->dimy);
		cart2d_grid_split(ctx->cart, ctx->global_grid);

		/*
		* TODO: Envoyer les dimensions de la grid dimensions et les données
		* Comment traiter le cas de rank=0 ?
		*/
		if (ctx->numprocs > 1) {
			int global_n_msgs = n_msgs * (ctx->numprocs - 1);
			MPI_Request *req = calloc(global_n_msgs, sizeof(MPI_Request)); 
			MPI_Status *status = calloc(global_n_msgs, sizeof(MPI_Status)); 
			int i ;

			for (i = 1; i < ctx->numprocs; i++) {
				int coords[DIM_2D];
				MPI_Cart_coords(ctx->comm2d, i, DIM_2D, coords);
				grid_t *grid = cart2d_get_grid(ctx->cart, coords[0], coords[1]);
				
				int offset_i = n_msgs * (i - 1);
				MPI_Isend(&grid->width, 1, MPI_INTEGER, i, width_tag, ctx->comm2d, req + offset_i);
				MPI_Isend(&grid->height, 1, MPI_INTEGER, i, height_tag, ctx->comm2d, req + offset_i + 1);
				MPI_Isend(&grid->padding, 1, MPI_INTEGER, i, padding_tag, ctx->comm2d, req + offset_i + 2);
				MPI_Isend(grid->data, grid->pw * grid->ph, MPI_DOUBLE, i, data_tag, ctx->comm2d, req + offset_i + 3);
			}

			MPI_Waitall(n_msgs, req, status);
			free(req);
			free(status);
		}
		
		// traiter le cas de rank=0
		int master_coords[DIM_2D];
		MPI_Cart_coords(ctx->comm2d, ctx->rank, DIM_2D, master_coords);
		new_grid = cart2d_get_grid(ctx->cart, master_coords[0], master_coords[1]);
	} else {
		/*
		* TODO: Recevoir les dimensions de la grid
		* et stocker dans new_grid
		*/

		int w, h, pad;
		MPI_Request req[4];
		MPI_Status status[4];

		MPI_Irecv(&w, 1, MPI_INTEGER, 0, width_tag, ctx->comm2d, req);
		MPI_Irecv(&h, 1, MPI_INTEGER, 0, height_tag, ctx->comm2d, req + 1);
		MPI_Irecv(&pad, 1, MPI_INTEGER, 0, padding_tag, ctx->comm2d, req + 2);

		MPI_Waitall(3, req, status);

		new_grid = make_grid(w, h, pad);

		MPI_Irecv(new_grid->data, new_grid->pw * new_grid->ph, MPI_DOUBLE, 0, data_tag, ctx->comm2d, &req[3]);
		MPI_Wait(&req[3], &status[3]);
	}

		

	/* Utilisation temporaire de global_grid */
	//new_grid = ctx->global_grid;

	if (new_grid == NULL)
		goto err;

	/* set padding required for Runge-Kutta */
	ctx->curr_grid = grid_padding(new_grid, 1);
	ctx->next_grid = grid_padding(new_grid, 1);
	ctx->heat_grid = grid_padding(new_grid, 1);
	//free_grid(new_grid);

	/* TODO: Créer un type vector pour échanger les colonnes */

	MPI_Type_vector(ctx->curr_grid->height, 1, ctx->curr_grid->pw, MPI_DOUBLE, &ctx->vector);
	MPI_Type_commit(&ctx->vector);

	return 0;
	err: return -1;
}



void exchng2d(ctx_t *ctx) {
	/*
	 *  TODO: Échanger les bordures avec les voisins
	 * 4 échanges doivent etre effectués
	 */
	
	grid_t *grid = ctx->curr_grid;
	int width = grid->width;
	// int height = grid->height;
	int pad_width = grid->pw;
	int pad_height = grid->ph;
	int pad = grid->padding;
	double *data = grid->data;
	int north = ctx->north_peer;
	int south = ctx->south_peer;
	int east = ctx->east_peer;
	int west = ctx->west_peer;
	MPI_Comm comm = ctx->comm2d;
	MPI_Request req[8];
	MPI_Status status[8];

	double *north_data_offset_send = data + (pad_width + 1) * pad;
	double *south_data_offset_send = data + (pad_height - pad - 1) * pad_width + pad;
	double *east_data_offset_send = north_data_offset_send + width - 1;
	double *west_data_offset_send = north_data_offset_send;

	double *north_data_offset_recv = north_data_offset_send - pad_width;
	double *south_data_offset_rec = south_data_offset_send + pad_width;
	double *east_data_offset_recv = east_data_offset_send + 1;
	double *west_data_offset_recv = west_data_offset_send - 1;

	MPI_Irecv(north_data_offset_recv, width, MPI_DOUBLE, north, 1, comm, req);
	MPI_Irecv(south_data_offset_rec, width, MPI_DOUBLE, south, 0, comm, req + 1);
	MPI_Irecv(east_data_offset_recv, 1, ctx->vector, east, 3, comm, req + 2);
	MPI_Irecv(west_data_offset_recv, 1, ctx->vector, west, 2, comm, req + 3);

	MPI_Isend(north_data_offset_send, width, MPI_DOUBLE, north, 0, comm, req + 4);
	MPI_Isend(south_data_offset_send, width, MPI_DOUBLE, south, 1, comm, req + 5);
	MPI_Isend(east_data_offset_send, 1, ctx->vector, east, 2, comm, req + 6);
	MPI_Isend(west_data_offset_send, 1, ctx->vector, west, 3, comm, req + 7);

	MPI_Waitall(8, req, status);
}

int gather_result(ctx_t *ctx, opts_t *opts) {

	int ret = 0;
	grid_t *local_grid = grid_padding(ctx->next_grid, 0);
	if (local_grid == NULL)
		goto err;

	if (ctx->rank == 0) {
		MPI_Request * req = calloc(ctx->numprocs - 1, sizeof(MPI_Request));
		MPI_Status * status = calloc(ctx->numprocs - 1, sizeof(MPI_Status));
		grid_t * grid;
		int coords[DIM_2D];
		int i;

		MPI_Cart_coords(ctx->comm2d, 0, DIM_2D, coords);
		grid = cart2d_get_grid(ctx->cart, coords[0], coords[1]);
		grid_copy(ctx->next_grid, grid);

		for (i = 1; i < ctx->numprocs; ++i) {
			MPI_Cart_coords(ctx->comm2d, i, DIM_2D, coords);

			grid = cart2d_get_grid(ctx->cart, coords[0], coords[1]);

			MPI_Irecv(grid->data, grid->height * grid->width, MPI_DOUBLE, i, 0, ctx->comm2d, (req + i - 1));
		}
		MPI_Waitall(ctx->numprocs - 1, req, status);

		cart2d_grid_merge(ctx->cart, ctx->global_grid);

		free(req);
		free(status);
	} else {
		MPI_Request req;
		MPI_Status status;

		MPI_Isend(local_grid->data, local_grid->height * local_grid->width, MPI_DOUBLE, 0, 0, ctx->comm2d, &req);
		MPI_Wait(&req, &status);
	}

	done: free_grid(local_grid);
	return ret;
	err: ret = -1;
	goto done;
}

int main(int argc, char **argv) {
	ctx_t *ctx = NULL;
	int rep, ret;
	opts_t opts;

	if (parse_opts(argc, argv, &opts) < 0) {
		printf("Error while parsing arguments\n");
		usage();
	}
	if (opts.verbose)
		dump_opts(&opts);

	MPI_Init(&argc, &argv);

	ctx = make_ctx();
	if (init_ctx(ctx, &opts) < 0)
		goto err;
	if (opts.verbose)
		dump_ctx(ctx);

	if (ctx->verbose) {
		fprintf(ctx->log, "heat grid\n");
		fdump_grid(ctx->heat_grid, ctx->log);
	}

	for (rep = 0; rep < opts.iter; rep++) {
		if (ctx->verbose) {
			fprintf(ctx->log, "iter %d\n", rep);
			fprintf(ctx->log, "start\n");
			fdump_grid(ctx->curr_grid, ctx->log);
		}

		grid_set_min(ctx->heat_grid, ctx->curr_grid);
		if (ctx->verbose) {
			fprintf(ctx->log, "grid_set_min\n");
			fdump_grid(ctx->curr_grid, ctx->log);
		}

		exchng2d(ctx);
		if (ctx->verbose) {
			fprintf(ctx->log, "exchng2d\n");
			fdump_grid(ctx->curr_grid, ctx->log);
		}

		heat_diffuse(ctx->curr_grid, ctx->next_grid);
		if (ctx->verbose) {
			fprintf(ctx->log, "heat_diffuse\n");
			fdump_grid(ctx->next_grid, ctx->log);
		}
		SWAP(ctx->curr_grid, ctx->next_grid);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	if (gather_result(ctx, &opts) < 0)
		goto err;

	if (ctx->rank == 0) {
		printf("saving...\n");
		if (save_grid_png(ctx->global_grid, opts.output) < 0) {
			printf("saving failed\n");
			goto err;
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	ret = EXIT_SUCCESS;
done:
	free_ctx(ctx);
	MPI_Finalize();
	FREE(opts.input);
	FREE(opts.output);
	return ret;
err:
	MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
	ret = EXIT_FAILURE;
	goto done;
}

