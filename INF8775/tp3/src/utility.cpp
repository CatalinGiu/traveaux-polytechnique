//
// Created by catalin on 4/13/19.
//

#include "utility.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>

using namespace std;

int compute_sum(int * data, int size){
    int ret = 0;
    for(int i = 0; i < size; i++){
        ret += data[i];
    }
    return  ret;
}

double compute_sum(double * data, int size){
    double ret = 0;
    for(int i = 0; i < size; i++){
        ret += data[i];
    }
    return  ret;
}

double compute_mean( int* data, int size)
{
    return compute_sum(data, size) / double(size);
}

// inspired from http://jonisalonen.com/2013/deriving-welfords-method-for-computing-variance/
double compute_variance(double* data, int size){
    double m = 0, s = 0, old_m;
    for(int i = 0; i < size; i++){
        old_m = m;
        m = m + (data[i] - m) / (i + 1);
        s = s + (data[i] - m) * (data[i] - old_m);
    }
    return  s / size;
}

void read_data(int *&inventory, int *&prices, int **&models, int &n_pieces, int &n_models, std::string &filepath) {
    string buffer;
    int i, j;
    ifstream file(filepath);
    if (file.is_open()) {
        file >> buffer;
        n_pieces = stoi(buffer);
        inventory = new int[n_pieces];
        prices = new int[n_pieces];
        for (i = 0; i < n_pieces; i++) {
            file >> buffer;
            inventory[i] = stoi(buffer);
        }
        for (i = 0; i < n_pieces; i++) {
            file >> buffer;
            prices[i] = stoi(buffer);
        }
        file >> buffer;
        n_models = stoi(buffer);
        models = new int*[n_models];
        for (i = 0; i < n_models; i++) {
            models[i] = new int[n_pieces];
            for (j = 0; j < n_pieces; j++) {
                file >> buffer;
                models[i][j] = stoi(buffer);
            }
        }
    }
    file.close();
}

void print_data(int *&inventory, int *&prices, int **&models, int &n_pieces, int &n_models) {
    int i, j;
    cout << "There are " << n_pieces << " different types of pieces" << endl;
    cout << "Here is our inventory :" << endl;
    for (i = 0; i < n_pieces; i++) {
        cout << inventory[i] << " ";
    }
    cout << endl << "Here is their associated price :" << endl;
    for (i = 0; i < n_pieces; i++) {
        cout << prices[i] << " ";
    }
    cout << endl << "There are " << n_models << " different models" << endl;
    cout << "Here are the required pieces to build them :" << endl;
    for (i = 0; i < n_models; i++) {
        for (j = 0; j < n_pieces; j++)
            cout << models[i][j] << " ";
        cout << endl;
    }
}
