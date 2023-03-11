#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

/* Determine whether arguments can be added without overflow */
int uadd_ok(unsigned x, unsigned y) {
    unsigned sum = x + y;
    return sum >= x;
}

/* Determine whether adding arguments would cause overflow */
int uadd_ovf(unsigned x, unsigned y) {
    unsigned sum = x + y;
    return sum < x;
}

/* Test function */
int test_uadd_ok(unsigned x, unsigned y) {
    uint64_t lx = (uint64_t) x; // 64-bit unsigned int
    uint64_t ly = (uint64_t) y;
    return (lx + ly) == (x + y);
}

/* Test function */
int test_uadd_ovf(unsigned x, unsigned y) {
    uint64_t lx = (uint64_t) x;
    uint64_t ly = (uint64_t) y;
    return (lx + ly) != (x + y);
}

int main(int argc, char *argv[]) {
    unsigned x = argc > 1 ? strtoul(argv[1], NULL, 0) : UINT_MAX; // 32-bit unsigned int
    unsigned y = argc > 1 ? strtoul(argv[2], NULL, 0) : UINT_MAX;
    int ok = uadd_ok(x, y);
    int ovf = uadd_ovf(x, y);
    int tok = test_uadd_ok(x, y);
    int tovf = test_uadd_ovf(x, y);
    printf("x = %u, y = %u, x + y = %u\n", x, y, x + y);
    if (ok == tok)
        printf("uadd_ok = %d, test_uadd_ok = %d\n", ok, tok);
    if (ovf == tovf)
        printf("uadd_ovf = %d, test_uadd_ovf = %d\n", ovf, tovf);
    return 0;
}