//
// Created by catalin on 1/21/19.
//

#include "utilityFunctions.h"

#include <iostream>

using namespace std;
int64_t *getArrayFromFile(string filename, int* size) {
    *size = getArraySize(filename);
    int64_t * testset = new int64_t[*size];

    ifstream file(filename);
    string number;
    int pos = 0;
    if(file.is_open()){
        while(getline(file, number)){
            testset[pos++] = stoll(number);
        }
        file.close();
    }
    return testset;
}

int getArraySize(std::string filename) {
    string number = "";
    bool numberFound = false;
    for (char c : filename) {
        if(!numberFound && c == '_'){
            numberFound = true;
        }
        else if(numberFound){
            if(c == '_'){
                break;
            }
            number += c;
        }
    }
    return stoi(number);
}

/* Function to print an array */
void printArray(int64_t *arr, int size) {
    int i;
    for (i=0; i < size; i++)
        cout << arr[i] << " ";
}

void printTime(chrono::time_point<std::chrono::steady_clock> start, chrono::time_point<std::chrono::steady_clock> end)
{
	chrono::duration<double> s = end - start;
	cout << fixed << s.count() * 1000 << endl;
}
