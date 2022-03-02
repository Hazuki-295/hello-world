#include <iostream>
#include <cstring>
using namespace std;

// const int arraySize = 10;

int main() {
    int arraySize;
    cin >> arraySize;

    int myArray[arraySize] = {};  // all elements 0 in C++
    for (int i = 0; i < arraySize; i++) {
        printf("myArray[%d] = %d\n", i, myArray[i]);
    }

    return 0;
}