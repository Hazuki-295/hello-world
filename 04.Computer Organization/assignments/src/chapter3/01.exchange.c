/* csapp 3rd edition - P223 Data Movement Example */
long exchange(long *xp, long y) {
    long x = *xp;
    *xp = y;
    return x;
}