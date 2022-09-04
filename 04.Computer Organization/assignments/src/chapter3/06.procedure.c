#include <stdio.h>

/* csapp 3rd edition - P279 Program involving procedure calls and returns */
long leaf(long y) {
    return y + 2;
}

long top(long x) {
    return 2 * leaf(x - 5);
}

int main(int argc, char *argv[]) {
    long cval = top(100);
    printf("top(100) --> %ld\n", cval);
    return 0;
}

/* csapp 3rd edition - P283 Example of function with multiple arguments of different types */
void proc(long a1, long *a1p,
          int  a2, int  *a2p,
          short a3, short *a3p,
          char  a4, char  *a4p) {
    *a1p += a1;
    *a2p += a2;
    *a3p += a3;
    *a4p += a4;
}

long call_proc() { // P286
    long  x1 = 1; int  x2 = 2;
    short x3 = 3; char x4 = 4;
    proc(x1, &x1, x2, &x2, x3, &x3, x4, &x4);
    return (x1 + x2) * (x3 - x4);
}

/* csapp 3rd edition - P285 Example of procedure definition and call */
long swap_add(long *xp, long *yp) {
    long x = *xp;
    long y = *yp;
    *xp = y;
    *yp = x;
    return x + y;
}

long caller() {
    long arg1 = 534;
    long arg2 = 1057;
    long sum = swap_add(&arg1, &arg2);
    long diff = arg1 - arg2;
    return sum * diff;
}

/* csapp 3rd edition - P288 Code demonstrating use of callee-saved registers */
long Q(long a);

long P(long x, long y) {
    long u = Q(y);
    long v = Q(x);
    return u + v;
}