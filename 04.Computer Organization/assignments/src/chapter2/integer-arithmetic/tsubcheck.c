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

/* Determine whether arguments can be subtracted without overflow */
int tsub_ok(int x, int y) {
    if (y == INT_MIN) {
        return x < 0; // while x is negative, there is no overflow
    }
    return tadd_ok(x, -y);
}

/* Test function */
int test_tsub_ok(int x, int y) {
    int64_t lx = (int64_t) x;
    int64_t ly = (int64_t) y;
    return (lx - ly) == (x - y);
}

int main(int argc, char *argv[]) {
    int x = argc > 1 ? atoi(argv[1]) : INT_MIN;
    int y = argc > 1 ? atoi(argv[2]) : INT_MIN;
    int ok = tsub_ok(x, y);
    int tok = test_tsub_ok(x, y);
    printf("x = %d, y = %d, x + y = %d\n", x, y, x + y);
    if (ok == tok)
        printf("tsub_ok = %d, test_tsub_ok = %d\n", ok, tok);
    return 0;
}