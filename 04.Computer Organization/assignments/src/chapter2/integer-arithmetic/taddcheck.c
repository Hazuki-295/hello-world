#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y) {
    int sum = x + y;
    int neg_over = x < 0 && y < 0 && sum >= 0;
    int pos_over = x > 0 && y > 0 && sum < 0;
    return !neg_over & !pos_over;
}

/* Determine whether adding arguments would cause overflow */
int tadd_ovf(int x, int y) {
    int sum = x + y;
    int neg_over = x < 0 && y < 0 && sum >= 0;
    int pos_over = x > 0 && y > 0 && sum < 0;
    return neg_over || pos_over;
}

/* Test function */
int test_tadd_ok(int x, int y) {
    int64_t lx = (int64_t) x; // sign extension, 64-bit two's complement int
    int64_t ly = (int64_t) y;
    return (lx + ly) == (x + y);
}

/* Test function */
int test_tadd_ovf(int x, int y) {
    int64_t lx = (int64_t) x;
    int64_t ly = (int64_t) y;
    return (lx + ly) != (x + y);
}

int main(int argc, char *argv[]) {
    int x = argc > 1 ? atoi(argv[1]) : INT_MAX; // 32-bit two's complement int
    int y = argc > 1 ? atoi(argv[2]) : INT_MAX;
    int ok = tadd_ok(x, y);
    int ovf = tadd_ovf(x, y);
    int tok = test_tadd_ok(x, y);
    int tovf = test_tadd_ovf(x, y);
    printf("x = %d, y = %d, x + y = %d\n", x, y, x + y);
    if (ok == tok)
        printf("tadd_ok = %d, test_tadd_ok = %d\n", ok, tok);
    if (ovf == tovf)
        printf("tadd_ovf = %d, test_tadd_ovf = %d\n", ovf, tovf);
    return 0;
}