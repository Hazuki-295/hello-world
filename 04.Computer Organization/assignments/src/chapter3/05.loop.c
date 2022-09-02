/* csapp 3rd edition - P257 do-while version of factorial program */
long fact_do(long n) {
    long result = 1;
    do {
        result *= n;
        n = n - 1;
    } while (n > 1);
    return result;
}

long fact_do_goto(long n) {
    long result = 1;
loop:
    result *= n;
    n = n - 1;
    if (n > 1) goto loop;
    return result;
}

/* csapp 3rd edition - P260 while version of factorial program */
long fact_while(long n) { // actually neither jump-to-middle nor guarded-do translation with gcc -Og
    long result = 1;
    while (n > 1) {
        result *= n;
        n = n - 1;
    }
    return result;
}

long fact_while_jm_goto(long n) { // P260 jump-to-middle translation
    long result = 1;
    goto test;
loop:
    result *= n;
    n = n - 1;
test:
    if (n > 1) goto loop;
    return result;
}

long fact_while_gd_goto(long n) { // P263 guarded-do translation
    long result = 1;
    if (n <= 1) goto done;
loop:
    result *= n;
    n = n - 1;
    if (n != 1) goto loop;
done:
    return result;
}

/* csapp 3rd edition - P265 for version of factorial program */
long fact_for(long n) {
    long i;
    long result = 1;
    for (i = 2; i <= n; i++)
        result *= i;
    return result;
}

long fact_for_while(long n) {
    long i = 2;
    long result = 1;
    while (i <= n) {
        result *= i;
        i++;
    }
    return result;
}

long fact_for_jm_goto(long n) {
    long i = 2;
    long result = 1;
    goto test;
loop:
    result *= i;
    i++;
test:
    if (i <= n)
        goto loop;
    return result;
}

long fact_for_gd_goto(long n) {
    long i = 2;
    long result = 1;
    if (n <= 1)
        goto done;
loop:
    result *= i;
    i++;
    if (i <= n)
        goto loop;
done:
    return result;
}

long rfact(long n) {
    long result;
    if (n <= 1)
        result = 1;
    else
        result = n * rfact(n - 1);
    return result;
}