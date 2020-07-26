//
// Created by catalin on 2/4/19.
//

#ifndef TP1_QUICK_H
#define TP1_QUICK_H

static int RAND_PIVOT;
static int THRESHOLD;
bool print_time;
bool print_array;

void quicksort(int64_t * arr, int lo, int hi);
int partition(int64_t * arr, int lo, int hi);
void bubblesort(int64_t * arr, int lo, int hi);
void printArray(int64_t * arr, int size);

#endif //TP1_QUICK_H
