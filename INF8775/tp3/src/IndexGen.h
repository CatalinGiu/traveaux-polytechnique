//
// Created by catalin on 4/14/19.
//
//  classe basee sur l'alogithme d'aceptance stochastique https://en.wikipedia.org/wiki/Fitness_proportionate_selection
//

#ifndef TP3_INDEXGEN_H
#define TP3_INDEXGEN_H

#include <random>


class IndexGen {
public:
    IndexGen(double* data, int max_index);
    IndexGen(int* data, int max_index);

    void update_generator(double* new_data);
    void update_generator(int* new_data);

    int new_index();
    void print_probs();

    virtual ~IndexGen();

private:
    void compute_probabilities(double *data);
    void compute_probabilities(int *data);

    double* probabilities;
    double max_probability;
    int max_index;

//    std::random_device rd;
    std::mt19937 mt;
    std::uniform_real_distribution<double>  index_rand;
    std::uniform_real_distribution<double> prob_rand;
};


#endif //TP3_INDEXGEN_H
