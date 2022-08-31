/* csapp 3rd edition - P248 Practice Problem 3.16 */
void cond(long a, long *p) {
    if (p && a < *p) {
        *p = a;
    }
}

void goto_cond(long a, long *p) { // goto version of cond
    if (p == 0) {
        goto done;
    }
    if (a >= *p) {
        goto done;
    }
    *p = a;
    done:
    return;
}