#include <stdio.h>

struct rec {
    int i;
    int j;
    int a[2];
    int *p;
};

void print_rec(struct rec *r) {
    printf("r -> [ i = %d, j = %d, a[0] = %d, a[1] = %d, p = %p ]\n", r->i, r->j, r->a[0], r->a[1], r->p);
}

int main() {
    struct rec obj = {0, 1, {2, 3}, &obj.a[1]};
    struct rec *r = &obj;
    int *p;
    print_rec(r);

    r->j = r->i;    // example1
    p = &(r->a[1]); // example2
    r->p = &(r->a[r->i + r->j]); // example3

    print_rec(r);
    printf("%p", p);

    return 0;
}