#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void unix_error(char *msg) {  /* Unix-style error */
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void sigint_handler(int sig) { /* SIGINT handler */
    printf("Caught SIGINT!\n");
    exit(0);
}

int main() {
    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        unix_error("signal error");
    }

    pause(); /* Wait for the receipt of a signal */

    return 0;
}