/* csapp 3rd edition - P297 Code computing matrix product for fixed-length arrays */
#define N 16
typedef int fix_matrix[N][N];

/* Compute i,k of fixed matrix product, original C code */
int fix_prod_ele(fix_matrix A, fix_matrix B, long i, long k) {
    long j;
    int result = 0;

    for (j = 0; j < N; j++)
        result += A[i][j] * B[j][k];

    return result;
}

/* Compute i,k of fixed matrix product, optimized C code */
int fix_prod_ele_opt(fix_matrix A, fix_matrix B, long i, long k) {
    int *Aptr = &A[i][0];    /* Points to elements in row i of A    */
    int *Bptr = &B[0][k];    /* Points to elements in column k of B */
    int *Bend = &B[N][k];    /* Marks stopping point for Bptr       */
    int result = 0;
    do {                          /* No need for initial test */
        result += *Aptr * *Bptr;  /* Add next product to sum  */
        Aptr++;                   /* Move Aptr to next column */
        Bptr += N;                /* Move Bptr to next row    */
    } while (Bptr != Bend);       /* Test for stopping point  */
    return result;
}

/* csapp 3rd edition - P300 Code computing matrix product for variable-size arrays */
/* Compute i,k of variable matrix product, original C code */
int var_prod_ele(long n, int A[n][n], int B[n][n], long i, long k) {
    long j;
    int result = 0;

    for (j = 0; j < n; j++)
        result += A[i][j] * B[j][k];

    return result;
}

/* Compute i,k of variable matrix product, optimized C code */
int var_prod_ele_opt(long n, int A[n][n], int B[n][n], long i, long k) {
    int *Arow = A[i];
    int *Bptr = &B[0][k];
    int result = 0;
    long j;
    for (j = 0; j < n; j++) {
        result += Arow[j] * *Bptr;
        Bptr += n;
    }
    return result;
}