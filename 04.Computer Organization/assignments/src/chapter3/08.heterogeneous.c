/* csapp 3rd edition - P301 Structures */
struct rec {
    int i;     /* offset 0  */
    int j;     /* offset 4  */
    int a[2];  /* offset 8  */
    int *p;    /* offset 16 */
};

void copy(struct rec *r) { // example1
    r->j = r->i;
}

int *find_a(struct rec *r, long i) { // example2
    return &r->a[i];
}

void link_p(struct rec *r) { // example3
    r->p = &r->a[r->i + r->j];
}