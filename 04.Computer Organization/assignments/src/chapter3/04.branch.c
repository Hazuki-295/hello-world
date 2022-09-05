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

/* csapp 3rd edition - P270 Example switch statement and its translation into extended C */
void switch_eg(long x, long n, long *dest) {
    long val = x;
    switch (n) {
        case 100:
            val *= 13;
            break;
        case 102:
            val += 10;
            /* Fall through */
        case 103:
            val += 11;
            break;
        case 104:
        case 106:
            val *= val;
            break;
        default:
            val = 0;
    }
    *dest = val;
}

void switch_eg_impl(long x, long n, long *dest) {
    /* Table of code pointers */
    static void *jt[7] = {
            &&loc_A, &&loc_def, &&loc_B,
            &&loc_C, &&loc_D, &&loc_def,
            &&loc_D
    };
    unsigned long index = n - 100;
    long val;

    if (index > 6) goto loc_def;
    /* Multiway branch */
    goto *jt[index];

loc_A:    /* Case 100 */
    val = x * 13;
    goto done;
loc_B:    /* Case 102 */
    x = x + 10;
    /* Fall through */
loc_C:    /* Case 103 */
    val = x + 11;
    goto done;
loc_D:    /* Cases 104, 106 */
    val = x * x;
    goto done;
loc_def:  /* Default case */
    val = 0;
done:
    *dest = val;
}