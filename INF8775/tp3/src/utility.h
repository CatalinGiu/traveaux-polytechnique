//
// Created by catalin on 4/13/19.
//

#ifndef TP3_UTILITY_H
#define TP3_UTILITY_H

#include <string>
#include <vector>

void read_data(int *&inventory, int *&prices, int **&models, int &n_pieces, int &n_models, std::string &filepath);
void print_data(int *&inventory, int *&prices, int **&models, int &n_pieces, int &n_models);
double compute_mean( int* data, int size);
int compute_sum(int * data, int size);
double compute_sum(double * data, int size);
double compute_variance(double* data, int size);


#endif //TP3_UTILITY_H
