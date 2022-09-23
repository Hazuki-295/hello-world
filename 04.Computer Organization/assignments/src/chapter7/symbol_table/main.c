#include <stdio.h>

int value1 = 1; /* strong symbol - .data section */
int value2 = 0; /* strong symbol - .bss section */
int value3;     /* weak symbol - COMMON */

void func(int sum) {
    printf("sum is:%d\n", sum);
}

int main() {
    static int a = 1; /* static local variable - .data section */
    static int b = 0; /* static local variable - .bss section */
    static int c;     /* static local variable - .bss section */
    int x = 12345; /* nonstatic local variable - run time stack */
    func(a + b + c + x);
    return 0;
}