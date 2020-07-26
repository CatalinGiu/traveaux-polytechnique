//
// Created by catalin on 3/15/19.
//

#ifndef TP2_SHARED_H
#define TP2_SHARED_H

#define EXTENDED_PRINT false
#define PRINT_REVENU true

#include <string>
#include <set>
#include <chrono>

typedef struct {
    int i;
    int r_i;
    int q_i;
}emplacement;

emplacement* get_emplacements_from_file(std::string& filename, int* size, int* capacity);

void print_emplacements(emplacement* emplacements, int size);
void print_solution(std::set<int> &solution, emplacement* emplacements, bool extended_print=false);
void printTime(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> end);
void print_revenu(std::set<int> &solution, emplacement* emplacements);

#endif //TP2_SHARED_H
