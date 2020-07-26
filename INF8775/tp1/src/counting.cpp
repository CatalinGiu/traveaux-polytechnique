//
// Created by catalin on 1/21/19.
//

#include "utilityFunctions.h"
#include "counting.h"

#include <iostream>
#include <string>
#include <cstring>

using namespace std;
int main(int argc, char* argv[]){
    int size;

    string filename = string(argv[1]);
    print_array = false;
    print_time = false;

    int64_t * arr = getArrayFromFile(filename, &size);
    for (int i = 2; i < argc; i++)
    {
	string arg(argv[i]);
    	if (arg == "-p")
        	print_array = true;
        else if (arg == "-t")
        	print_time = true;
    }
    auto start = chrono::steady_clock::now();
    int64_t* sorted_arr = counting(arr, size);
    auto end = chrono::steady_clock::now();
    if(sorted_arr != nullptr) {
        if (print_array)
            printArray(sorted_arr, size);
        if (print_time)
            printTime(start, end);
    }
    else{
        cout << "-1" << endl;
    }
    delete[] arr;
    return 0;
}

int64_t* counting(int64_t arr[], int size){
    int64_t max = maximum(arr, size);
    int64_t* count;
    try {
        count = new int64_t [max + 1];
    }catch (exception& e){
        return nullptr;
    }
    int64_t* ret = new int64_t[size];

    memset(count, 0, max * sizeof(int64_t));

    for(int i = 0; i < size; i++){
        count[arr[i]]++;
    }

    for(int i = 1; i <= max; i++){
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; --i)
    {
        ret[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }
    delete[] count;
    return ret;
}

int64_t maximum(int64_t *arr, int size) {
    int64_t max = 0;
    for(int i = 0; i < size; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}
