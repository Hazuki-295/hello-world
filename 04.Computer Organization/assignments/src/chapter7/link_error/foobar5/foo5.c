#include <stdio.h>

void f();

int y = 15212; /* defined first, but higher address */
int x = 15213;

typedef struct {
    int x;
    int y; /* higher address */
} internal;

internal double2ints(double d) {
    union {
        internal ints;
        double d;
    } temp;
    temp.d = d;
    return temp.ints;
}

void test_union() {
    internal s = double2ints(-0.0);
    printf("x = 0x%x y = 0x%x \n", s.x, s.y);
}

int main() {
    f();
    printf("x = 0x%x y = 0x%x \n", x, y);
    test_union();
    return 0;
}