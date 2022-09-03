/* csapp 3rd edition - P246 Implementing Conditional Branches With Conditional Control */
long lt_cnt = 0;
long ge_cnt = 0;

long absdiff_se(long x, long y) {
    long result;
    if (x < y) {
        lt_cnt++;
        result = y - x;
    } else {
        ge_cnt++;
        result = x - y;
    }
    return result;
}

long gotodiff_se(long x, long y) {
    long result;
    if (x >= y) goto x_ge_y;
    lt_cnt++;
    result = y - x;
    return result;
x_ge_y:
    ge_cnt++;
    result = x - y;
    return result;
}

/* csapp 3rd edition - P248 Practice Problem 3.16 */
void cond(long a, long *p) {
    if (p && a < *p) {
        *p = a;
    }
}

void goto_cond(long a, long *p) {
    if (p == 0)
        goto done;
    if (a >= *p)
        goto done;
    *p = a;
done:
    return;
}

/* csapp 3rd edition - P250 Implementing Conditional Branches With Conditional Moves */
long absdiff(long x, long y) { // using -O1 flag instead of -Og
    long result;
    if (x < y)
        result = y - x;
    else
        result = x - y;
    return result;
}

long cmovdiff(long x, long y) {
    long rval = y - x;
    long eval = x - y;
    long ntest = x >= y;
    if (ntest) rval = eval; // This statement requires single instruction
    return rval;
}

/* csapp 3rd edition - P254 Implementing Conditional Operations With Conditional Moves */
long foo(long x, long y) {
    return x > y ? ++x : ++y;
}

long cread(long *xp) {
    return xp ? *xp : 0; // statement that could not be implemented with conditional moves
}