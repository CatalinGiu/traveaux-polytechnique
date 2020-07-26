//
// Created by catalin on 4/14/19.
//

#include "IndexGen.h"
#include "utility.h"
#include <random>
#include <chrono>
#include <iostream>

using namespace std;
int IndexGen::new_index() {
    int index;
    double prob;

    while (true) {
        index = int(this->index_rand(this->mt));
        prob = this->prob_rand(this->mt);
        if (prob < (this->probabilities[index] / this->max_probability))
            return index;
    }
}

IndexGen::IndexGen(double *data, int max_index) : max_index(max_index){
    this->probabilities = new double[max_index];
    this->compute_probabilities(data);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    this->mt = mt19937(seed);
    this->index_rand = uniform_real_distribution<double>(0, max_index);
    this->prob_rand = uniform_real_distribution<double>(0, 1);
}

IndexGen::~IndexGen() {
    try {
        delete[] this->probabilities;
    }
    catch (exception& e){
        ; // the table was not dynamically allocated;
    }

}

void IndexGen::update_generator(double *data){
    compute_probabilities(data);
}

void IndexGen::compute_probabilities(double *data) {
    this->max_probability = 0;
    double sum = compute_sum(data, this->max_index);
    if(sum <= 0){
        return;
    }

    for (int i = 0; i < this->max_index; i++) {
        if(data[i]) {
            this->probabilities[i] = sum / data[i];
        }
        else{
            this->probabilities[i] = 0;
        }
    }
    sum = compute_sum(this->probabilities, this->max_index);
    for (int i = 0; i < this->max_index; i++) {
        this->probabilities[i] = this->probabilities[i] / sum;
        if (this->probabilities[i] > this->max_probability) {
            this->max_probability = this->probabilities[i];
        }
    }
}

IndexGen::IndexGen(int *data, int max_index) : max_index(max_index) {
    this->probabilities = new double[max_index];
    this->compute_probabilities(data);

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    this->mt = mt19937(seed);
    this->index_rand = uniform_real_distribution<double>(0, max_index);
    this->prob_rand = uniform_real_distribution<double>(0, 1);
}

void IndexGen::update_generator(int *new_data) {
    compute_probabilities(new_data);
}

void IndexGen::compute_probabilities(int *data) {
    this->max_probability = 0;
    double sum = compute_sum(data, this->max_index);

    for (int i = 0; i < this->max_index; i++) {
        if(data[i]) {
            this->probabilities[i] = sum / data[i];
        }
        else{
            this->probabilities[i] = 0;
        }
    }
    sum = compute_sum(this->probabilities, this->max_index);
    for (int i = 0; i < this->max_index; i++) {
        this->probabilities[i] = this->probabilities[i] / sum;
        if (this->probabilities[i] > this->max_probability) {
            this->max_probability = this->probabilities[i];
        }
    }
}

void IndexGen::print_probs() {
    cout << "PROBABILITIES\n";
    for( int i = 0; i < this->max_index; i++)
        cout << this->probabilities[i] << " ";
    cout << endl;
}
