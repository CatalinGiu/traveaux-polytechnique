//
// Created by catalin on 3/15/19.
//

#include "shared.h"

#include <iostream>
#include <fstream>

using namespace std;
emplacement *get_emplacements_from_file(string& filename, int* size, int* capacity) {
    ifstream file(filename);
    emplacement* emplacements = nullptr;
    int pos = 0;
    string input_i, input_ri, input_qi;
    if(file.is_open()){
        file >> input_i; // actually size but i don't want another variable
        *size = stoi(input_i);
        emplacements = new emplacement[*size];
        while(pos < *size){
            file >> input_i >> input_ri >> input_qi; // i
            emplacements[pos].i = stoi(input_i);
            emplacements[pos].r_i = stoi(input_ri);
            emplacements[pos].q_i = stoi(input_qi);
            pos++;
        }
        file >> input_i; // actually capacity but i don't want another variable
        *capacity = stoi(input_i);
    }
    return emplacements;
}

void print_emplacements(emplacement *emplacements, int size) {
    cout << size << endl;
    for(int i = 0; i < size ; i++){
        cout << emplacements[i].i << "\t" << emplacements[i].r_i << "\t" << emplacements[i].q_i << "\t" << endl;
    }
}

void print_solution(set<int> &solution, emplacement* emplacements, bool extended_print) {
    int qi_sum = 0;
    for(int i : solution) {
        cout << emplacements[i].i << " ";
        if (extended_print) {
            cout << emplacements[i].r_i << " " << emplacements[i].q_i << endl;
            qi_sum += emplacements[i].q_i;
        }
    }
    if(extended_print){
        cout << qi_sum;
    }
    cout << endl;
}

void printTime(chrono::time_point<std::chrono::steady_clock> start, chrono::time_point<std::chrono::steady_clock> end)
{
    chrono::duration<double> s = end - start;
    cout << fixed << s.count() * 1000 << endl;
}

void print_revenu(std::set<int> &solution, emplacement *emplacements) {
    int ri_sum = 0;
    for (int i : solution) {
        ri_sum += emplacements[i].r_i;
    }
    cout << ri_sum << ",";
}



