#include <iostream>
using namespace std;

constexpr int size = 3000000;
int a[size] = {};
/**********************************************************************************************
 * 如果数组的规模较大(megabyte 数量级，10^6 bytes)：
 * 1. 局部变量：如放在 main 函数中，是从”调用栈(call stack)“申请空间，允许申请的空间较小，会导致程序异常退出。
 * 2. 全局变量：编译阶段，在”数据段(data segment)“中分配空间，允许申请的空间较大。
 **********************************************************************************************/

int main() {
    int *b = (int *)malloc(sizeof(int) * size);  // 或者在堆上申请
    for (int i = 0; i < size; i++) {
        b[i] = i;
    }
    free(b);

    int myArray[10] = {};  // all elements 0 in C++
    for (int i = 0; i < 10; i++) {
        printf("myArray[%d] = %d\n", i, myArray[i]);
    }

    return 0;
}