//
// Created by catalin on 1/21/19.
//

#ifndef TP1_UTILIYFUNCTIONS_H
#define TP1_UTILIYFUNCTIONS_H

#include <string>
#include <fstream>
#include <chrono>

int getArraySize(std::string filename);
int64_t * getArrayFromFile(std::string filename, int * size);
void printArray(int64_t * arr, int size);
void printTime(std::chrono::time_point<std::chrono::steady_clock> start, std::chrono::time_point<std::chrono::steady_clock> end);

#endif //TP1_UTILIYFUNCTIONS_H
