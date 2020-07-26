//
// Created by catalin on 3/21/19.
//
#include "glouton.h"
#include "shared.h"
#include <string>

using namespace std;
int main(int argc, char* argv[]) {
    string filepath;
    bool print_array = false;
    bool print_time = false;

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

    auto start = chrono::steady_clock::now();
    set<int> solution = setup_and_run_glouton(emplacements, size, capacity);
    auto end = chrono::steady_clock::now();

    if(print_array)
        print_solution(solution, emplacements, EXTENDED_PRINT);
    if(PRINT_REVENU)
        print_revenu(solution, emplacements);
    if (print_time)
        printTime(start, end);

    delete[] emplacements;
    return 0;
}