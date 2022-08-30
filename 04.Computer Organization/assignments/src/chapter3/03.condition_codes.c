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

int long_int_equal(long a, long b) { // D
    return a == b;
}

int unsigned_long_int_equal(unsigned long a, unsigned long b) { // D
    return a == b;
}

int pointer_equal(char *a, char *b) { // D
    return a == b;
}

#define TEST !=

/* csapp 3rd edition - P240 Practice Problem 3.14 */
int test(data_t a) {
    return a TEST 0;
}

int test_lige(long a) {
    return a >= 0;
}

int test_wz(short a) {
    return a == 0;
}

int test_uwz(unsigned short a) {
    return a == 0;
}

int test_cgt(char a) {
    return a > 0;
}

int test_ile(int a) {
    return a <= 0;
}