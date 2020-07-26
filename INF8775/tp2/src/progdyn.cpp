//
// Created by catalin on 3/16/19.
//

#include "progdyn.h"

#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
    string filepath;
    bool print_array = false;
    bool print_time = false;
    run_successful = false;

    for (int i = 1; i < argc; i++)
    {
        string arg(argv[i]);
        if (arg == "-p")
            print_array = true;
        else if (arg == "-t")
            print_time = true;
        else
            filepath = arg;
    }

    int size, capacity;
    emplacement* emplacements = get_emplacements_from_file(filepath, &size, &capacity);

    capacity += 1;

    int** mem;
    auto start = chrono::steady_clock::now();
    try {
        mem = new int*[size];
        for (int i = 0; i < size; i++) {
            mem[i] = new int[capacity];
        }
        set_frontiers(emplacements, mem, size, capacity);
        progdyn(emplacements, size, capacity, mem);
        run_successful = true;
    }catch(exception e) {
        ; // continue to dealocation
    }
    auto end = chrono::steady_clock::now();
    set<int> solution;
    if(run_successful) {
        solution = get_solution(emplacements, mem, size, capacity);
        if(print_array){
            print_solution(solution, emplacements, EXTENDED_PRINT);
        }
        if(PRINT_REVENU)
            print_revenu(solution, emplacements);
    }
    if (print_time)
        printTime(start, end);

    try {
        delete[] emplacements;
        for(int i = 0; i < size; i++)
            delete[] mem[i];
        delete[] mem;
    }catch(exception e){
        // ressource was most likely not allocated so we can exit
    }

    return 0;
}

void progdyn(emplacement *emplacements, int size, int capacity, int **mem) {
    // index starts at 1 to avoid SEG FAULT on mem[i-1]
    for(int i = 1; i < size; i++) {
        // with 0 capacity the revenue is trivially set to 0 along the whole column, therefore the capacity index starts at 1
        for(int j = 1; j < capacity; j++) {
            if (j >= emplacements[i].q_i) {
                mem[i][j] = max(emplacements[i].r_i + mem[i-1][j - emplacements[i].q_i], mem[i-1][j]);
            } else {
                mem[i][j] = mem[i-1][j];
            }
        }
    }
}

void set_frontiers(emplacement *emplacements, int **mem, int size, int capacity) {
    for(int i = 0; i < size; i++) {
        memset(mem[i], 0, capacity * sizeof(int));
    }

    for(int j = 0; j < capacity; j++){
        if(j < emplacements[0].q_i){
            mem[0][j] = 0;
        } else{
            mem[0][j] = emplacements[0].r_i;
        }
    }
}

set<int> get_solution(emplacement *emplacements, int **mem, int size, int capacity) {
    set<int> ret;
    int max_ri = mem[size - 1][capacity - 1];
    int i = size - 1;
    int j = capacity - 1;

    while(j > 0){
        while(--i >= 0 && mem[i][j] == max_ri){

        }
        ret.insert(i + 1);
        if(i < 0){ // went through all locations, time to stop
            break;
        }
        j -= emplacements[i + 1].q_i;
        max_ri = mem[i][j];
        i++;
    }
    return ret;
}


