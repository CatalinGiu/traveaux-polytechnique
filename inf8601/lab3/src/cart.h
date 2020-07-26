/*
 * cart.h
 *
 *  Created on: 2011-11-15
 *      Author: francis
 */

#ifndef CART_H_
#define CART_H_

#include "grid.h"

typedef struct cart2d {
	/* A 2d array of grids* */ 
	grid_t **grids;
	/* Dimension of the overall grid, which is the sum of the dimensions of the individual grids */ 
	int width;
	int height;
	/* Dimensions of the grid array. It contains block_x * block_y grids */
	int block_x;
	int block_y;
	/* 
	   dims stores the individual dimensions of the grids.
	   dims[0][i] contains the width of the ith column of blocks
	   dims[1][j] contains the height of the jth column of blocks
	*/
	int **dims;
	/* 
	   pos stores the starting positions of the different grids. (Sum of previous dimensions)
	   pos[0][i] contains the x offset of the ith column of blocks 
	   pos[1][j] contains the y offset of the jth column of blocks
	*/
	int **pos;
} cart2d_t;

cart2d_t *make_cart2d(int width, int height, int dim_x, int dim_y);
grid_t *cart2d_get_grid(cart2d_t *cart, int x, int y);
void cart2d_grid_merge(cart2d_t *cart, grid_t *grid);
void cart2d_grid_split(cart2d_t *cart, grid_t *grid);
void cart2d_padding(cart2d_t *cart, int padding);
void free_cart2d(cart2d_t *cart);
int **decomp2d(int width, int height, int block_x, int block_y);
int **decomp2d_pos(int **dims, int block_x, int block_y);
void free_decomp2d(int **dims);

#endif /* CART_H_ */
