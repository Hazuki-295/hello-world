#include <stdlib.h>

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

/* csapp 3rd edition - P307 Unions, the use of two fields in a data structure are mutually exclusive */
struct node_s {
    struct node_s *left;
    struct node_s *right;
    double data[2];
}; // 32 bytes

typedef enum {
    N_LEAF, N_INTERNAL
} nodetype_t;

struct node_t {
    nodetype_t type; // 4 bytes
    union {
        struct {
            struct node_t *left;
            struct node_t *right;
        } internal;
        double data[2];
    } info; // 16 bytes
}; // 24 bytes

/* csapp 3rd edition - P307 Unions, use unions to assess the bit patterns of different types */
unsigned long double2ulong(double d) {
    return (unsigned long) d;
};

unsigned long double2bits(double d) {
    union {
        double d;
        unsigned long u;
    } temp;
    temp.d = d;
    return temp.u;
}

double uu2double(unsigned word0, unsigned word1) { // P308
    union {
        double d;
        unsigned u[2];
    } temp;

    temp.u[0] = word0;
    temp.u[1] = word1;
    return temp.d;
}

/* csapp 3rd edition - P310 Data Alignment */
struct S1 {
    int i;  /* offset 0 */
    char c; /* offset 4 */
    int j;  /* offset 8 */
};

int test_S1(struct S1 *p) {
    int sum = p->i + p->c + p->j;
    size_t size = sizeof(struct S1);
    return sum + size;
}

struct S2 {
    int i;  /* offset 0 */
    int j;  /* offset 4 */
    char c; /* offset 8 */
};

int test_S2(struct S2 *p) {
    int sum = p->i + p->j + p->c;
    size_t size = sizeof(struct S2);
    return sum + size;
}