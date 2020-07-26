#ifndef TP2_LOCAL_H
#define TP2_LOCAL_H

#include "shared.h"
#include <vector>

void combinationUtil(std::vector<emplacement> arr, int r,int index,std::vector<emplacement> data, int i, std::vector<std::vector<emplacement>> &ret);
std::vector<std::vector<emplacement>> compute_compbination(std::vector<emplacement> arr, std::vector<emplacement> &curr_solution, int r);
std::vector<emplacement> local_optimization(std::vector<emplacement> &emplacements, std::vector<emplacement> solution);
int get_rentabilite(std::vector<emplacement> &emplacements);
int get_quantite(std::vector<emplacement> &emplacements);
void replace_emplacements_in_solution(std::vector<emplacement> &solution, std::vector<emplacement> &new_emplacements, std::vector<emplacement> &old_emplacements);
double time_elapsed(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> end);
std::vector<emplacement> find_best_combination(std::vector<std::vector<emplacement>> &combinations, int q_i);
#endif //TP2_LOCAL_H
