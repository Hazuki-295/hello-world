typedef long data_t;

#define COMP <

/* csapp 3rd edition - P240 Practice Problem 3.13 */
int comp(data_t a, data_t b) {
    return a COMP b;
}

int int_less_than(int a, int b) { // A
    return a < b;
}

int short_greater_or_equal(short a, short b) { // B
    return a >= b;
}

int unsigned_char_less_or_equal(unsigned char a, unsigned char b) { // C
    return a <= b;
}

int long_int_equal(long a, long b) { // D, replace not equal -> equal
    return a == b;
}

int unsigned_long_int_equal(unsigned long a, unsigned long b) { // D
    return a == b;
}

int pointer_equal(char *a, char *b) { // D
    return a == b;
}

#define TEST !=

/* csapp 3rd edition - P241 Practice Problem 3.14 */
int test(data_t a) {
    return a TEST 0;
}

int test_long_int_greater_or_equal(long a) { // A
    return a >= 0;
}

int test_short_zero(short a) { // B
    return a == 0;
}

int test_unsigned_short_zero(unsigned short a) { // B
    return a == 0;
}

int test_unsigned_char_greater_than(unsigned char a) { // C
    return a > 0;
}

int test_int_less_or_equal(int a) { // D
    return a <= 0;
}