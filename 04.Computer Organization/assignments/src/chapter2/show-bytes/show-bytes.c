#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(long val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    printf("Byte representations for %ld:\n", val);
    printf("show_int(%d) \t -> \t", ival);
    show_int(ival);
    printf("show_float(%f) \t -> \t", fval);
    show_float(fval);
    printf("show_pointer(%p) \t -> \t", pval);
    show_pointer(pval);
}

void simple_show_a() {
    int val = 0x87654321;
    byte_pointer valp = (byte_pointer) &val;
    show_bytes(valp, 1); /* A. */
    show_bytes(valp, 2); /* B. */
    show_bytes(valp, 3); /* C. */
}

void simple_show_b() {
    int val = 0x12345678;
    byte_pointer valp = (byte_pointer) &val;
    show_bytes(valp, 1); /* A. */
    show_bytes(valp, 2); /* B. */
    show_bytes(valp, 3); /* C. */
}

void float_eg() {
    int x = 3490593;
    float f = (float) x;
    printf("For x = %d\n", x);
    show_int(x);
    show_float(f);

    x = 3510593;
    f = (float) x;
    printf("For x = %d\n", x);
    show_int(x);
    show_float(f);
}

void string_ueg() {  /* Uppercase string */
    const char *s = "ABCDEF";
    show_bytes((byte_pointer) s, strlen(s));
}

void string_leg() {  /* Lowercase string */
    const char *s = "abcdef";
    show_bytes((byte_pointer) s, strlen(s));
}

void show_twocomp() {  /* Two's complement */
    short x = 12345;
    short mx = -x;

    show_bytes((byte_pointer) &x, sizeof(short));
    show_bytes((byte_pointer) &mx, sizeof(short));
}

int main(int argc, char *argv[]) {
    long val = 12345;

    if (argc > 1) {
        if (argc > 1) {
            val = strtol(argv[1], NULL, 0);
        }
        printf("[0] Calling test_show_bytes()\n");
        test_show_bytes(val);
    } else {
        printf("[1] Calling show_twocomp()\n");
        show_twocomp();
        printf("[2] Calling simple_show_a()\n");
        simple_show_a();
        printf("[3] Calling simple_show_b()\n");
        simple_show_b();
        printf("[4] Calling float_eg()\n");
        float_eg();
        printf("[5] Calling string_ueg()\n");
        string_ueg();
        printf("[6] Calling string_leg()\n");
        string_leg();
    }
    return 0;
}