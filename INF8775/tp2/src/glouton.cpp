#include "glouton.h"

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

std::set<int> setup_and_run_glouton(emplacement *emplacements, int size, int capacity) {
    set<int> solution, solution_candidatae;
    double max_probability = 0, max_rentability = 0, max_rentability_candidate = 0;

    double* probabilities = compute_probabilities(emplacements, &max_probability, size);

    for(int i = 0; i < N_RUNS; i++){
        solution_candidatae = glouton(emplacements, probabilities, size, capacity, max_probability);
        max_rentability_candidate = calc_rentabilite(solution_candidatae, emplacements);

        if(max_rentability_candidate > max_rentability){
            max_rentability = max_rentability_candidate;
            solution = solution_candidatae;
        }
    }

    delete[] probabilities;
    return solution;
}

// stochastic acceptance version of the Fitness proportionate selection algorithm
// based on the Java implementation at https://en.wikipedia.org/wiki/Fitness_proportionate_selection
set<int> glouton(emplacement *emplacements, double* probabilities, int size, int capacity, double max_prob) {
    // C++ 11 random library
    // https://stackoverflow.com/a/19666713
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> index_rand(0, size);
    uniform_real_distribution<double> prob_rand(0, 1);

    set<int> selected = set<int>();

    int consumption = 0;
    int attemts = 0;
    int max_attempts = int(sqrt(size));
    int index;
    double prob;
    while(capacity > consumption){
        while(true){
            index = int(index_rand(mt));
            prob = prob_rand(mt);
            if(prob < (probabilities[index] / max_prob))
                break;
        }
        if(emplacements[index].q_i <= (capacity - consumption) && selected.find(index) == selected.end()) {
            selected.insert(index);
            consumption += emplacements[index].q_i;
            attemts = 0;
        } else if(attemts++ > max_attempts){
            break;
        }

    }
    return selected;
}

double *compute_probabilities(emplacement *emplacements, double* max_prob, int size) {

    double* ret = new double[size];
    double rentability_sum = 0;

    for(int i = 0; i < size; i++){
        ret[i] = double(emplacements[i].r_i) / emplacements[i].q_i;
        rentability_sum += ret[i];
    }

    for(int i = 0; i < size; i++){
        ret[i] = ret[i] / rentability_sum;

        if(ret[i] > *max_prob)
            *max_prob = ret[i];
    }

    return ret;
}

double calc_rentabilite(std::set<int> &solution, emplacement* emplacements) {
    double rentabilite = 0;
    for(int index : solution){
        rentabilite += double(emplacements[index].r_i) / emplacements[index].q_i;
    }
    return rentabilite;
}
