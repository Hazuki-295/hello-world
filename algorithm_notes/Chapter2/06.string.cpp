#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int main() {
    int myArray[5] = {};

    /* memset - fill memory with a constant byte (interpreted as an unsigned char) */
    for (auto byte : vector<int>({0, -1, 1, 255})) {
        memset(myArray, byte, sizeof(myArray));

        printf("memset(byte: %3d) = ", byte);  // 0的补码为“全0”，-1的补码为“全1”，
        for (auto x : myArray) {               // 因此 memset 可用来将 int 数组的所有元素赋值为0或-1
            printf("%10d ", x);
        }
        printf("\n");
    }

    return 0;
}