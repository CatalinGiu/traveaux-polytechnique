//
// Created by catalin on 4/7/19.
//

#ifndef TP3_LEGO_H
#define TP3_LEGO_H

//#define PRINT_DATA

#include "IndexGen.h"
#include <string>

int inventory_value = 0;
int global_best_solution = INT32_MAX;
int max_attempts = 1000;

void compute_ratios(int* inventory, int* model, int size, double* ret_ratio);
void build_models_from_inventory(int* inventory, int n_pieces, int** models, int n_models, IndexGen& index_generator, int* solution);
bool model_fits(int* inventory, int* model, int n_pieces);
void copy_array(int* original, int* copy, int size);
void buy_models(int* inventory, int n_pieces, int** models, int n_models, int* solution, double* ratios, double* variances);
void evolve(int **parents, int **models, int *prices, int* initial_inventory, int n_pieces, int n_models, double* ratios, double* variance);
void breed(int* parent1, int* parent2, int* child, int n_model, IndexGen& fittyfitty, IndexGen& tchernobylizer);
int get_inventory_from_solution(int* solution, int* new_inventory, int n_pieces, int** models, int n_models, int* prices);
void print_solution(int* sol, int size, int price);
#endif //TP3_LEGO_H
