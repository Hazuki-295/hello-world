/* csapp 3rd edition - P223 Data Movement Example */
long exchange(long *xp, long y) {
    long x = *xp;
    *xp = y;
    return x;
}

/* csapp 3rd edition - P229 Load Effective Address, the leaq instruction */
long scale(long x, long y, long z) {
    long t = x + 4 * y + 12 * z;
    return t;
}

/* csapp 3rd edition - P231 Shift Operations */
long shift_left4_rightn(long x, long n) {
    x <<= 4;
    x >>= n;
    return x;
}

/* csapp 3rd edition - P232 Example of Arithmetic Operations */
long arith(long x, long y, long z) {
    long t1 = x ^ y;
    long t2 = z * 48;
    long t3 = t1 & 0x0F0F0F0F;
    long t4 = t2 - t3;
    return t4;
}