//
// Created by catalin on 1/21/19.
//

#include "utilityFunctions.h"
#include "quick.h"

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
int main(int argc, char* argv[])
{
    if(argc < 4){
        // invalid number of arguments
        cout << "./quick arr.txt pivot threshold" << endl;
        return 22;
    }
    srand (time(NULL));
    int size;
    print_array = false;
    print_time = false;

    string filename = string(argv[1]);
    RAND_PIVOT = stoi(argv[2]);
    THRESHOLD = stoi(argv[3]);
    for (int i = 4; i < argc; i++)
    {
	string arg(argv[i]);
    	if (arg == "-p")
        	print_array = true;
        else if (arg == "-t")
        	print_time = true;
    }



    int64_t * arr = getArrayFromFile(filename, &size);
    auto start = chrono::steady_clock::now();
    quicksort(arr, 0, size - 1);
    auto end = chrono::steady_clock::now();
    if (print_array)
    	printArray(arr, size);
    if (print_time)
	    printTime(start, end);

    delete[] arr;
    return 0;
}

int partition(int64_t * arr, int lo, int hi){
    int64_t pivot = arr[lo];
    int64_t tmp;

    if(RAND_PIVOT){
        pivot = arr[rand() % (hi - lo) + lo];
    }
    int i = lo - 1;
    int j = hi + 1;
    while(true){
        do{
            i++;
        }while (arr[i] < pivot);
        do{
            j--;
        }while (arr[j] > pivot);

        if(i >= j){
            return j;
        }
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void quicksort(int64_t * arr, int lo, int hi){
    int pivot;
    if(hi - lo < THRESHOLD){
        bubblesort(arr, lo, hi);
    }
    else if (lo < hi){
        pivot = partition(arr, lo, hi);
        quicksort(arr, lo, pivot);
        quicksort(arr, pivot + 1, hi);
    }
}

void bubblesort(int64_t *arr, int lo, int hi) {
    int64_t tmp;
    for (int i = 0; i < hi - lo; i++) {

        // Last i elements are already in place
        for (int j = lo; j < hi - i; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}





