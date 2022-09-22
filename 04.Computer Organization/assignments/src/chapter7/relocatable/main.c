#include <stdio.h>

int value1 = 10; /* strong symbol - .data section */
int value2 = 0;  /* strong symbol - .bss section */
int value3;      /* weak symbol - COMMON */

void func(int sum) {
    printf("sum is:%d\n", sum);
}

int main() {
    static int a = 1; /* .data section */
    static int b = 0; /* .bss section */
    int x = 1;
    func(a + b + x);
    return 0;
}