#include <stdio.h>

int sum(int *a, int n);

int array[2] = {295, 200};

int value1 = 1; /* strong symbol - .data section */
int value2 = 0; /* strong symbol - .bss section */
int value3;     /* weak symbol - COMMON */

int main() {
    static int a = 1; /* static local variable - .data section */
    static int b = 0; /* static local variable - .bss section */
    static int c;     /* static local variable - .bss section */
    int x = 12345; /* nonstatic local variable - run time stack */

    int var = sum(array, 2);
    printf("sum is:%d\n", var + a + b + c + x);
    return 0;
}