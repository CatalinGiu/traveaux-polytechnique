//
// Created by catalin on 3/15/19.
//

#ifndef TP2_GLOUTON_H
#define TP2_GLOUTON_H

#include "shared.h"
#include <set>

#define N_RUNS 10

std::set<int> glouton(emplacement* emplacements, double* probabilities, int size, int capacity, double max_prob);
double* compute_probabilities(emplacement* emplacements, double* max_prob, int size);
double calc_rentabilite(std::set<int> &solution, emplacement* emplacements);
std::set<int> setup_and_run_glouton(emplacement* emplacements, int size, int capacity);

#endif //TP2_GLOUTON_H
