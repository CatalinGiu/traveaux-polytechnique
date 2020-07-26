//
// Created by catalin on 3/16/19.
//

#ifndef TP2_PROGDYN_H
#define TP2_PROGDYN_H

#include "shared.h"

bool run_successful;

void progdyn(emplacement* emplacements, int size, int capacity, int** mem);

void set_frontiers(emplacement *emplacements, int **mem, int size, int capacity);
std::set<int> get_solution(emplacement* emplacements, int** mem, int size, int capacity);

#endif //TP2_PROGDYN_H
