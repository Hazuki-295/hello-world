#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void unix_error(char *msg) { /* Unix-style error */
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void sigint_handler(int sig) { /* SIGINT handler */
    printf("\rCaught SIGINT!\n");
    return;
}

unsigned int snooze(unsigned int secs) {
    unsigned int rc = sleep(secs);
    printf("Slept for %d of %d secs.\n", secs - rc, secs);
    return rc;
}

int main() {
    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        unix_error("signal error");
    }

    unsigned int rc = snooze(10); /* Wait for the receipt of a signal */

    if (!rc) printf("Where is mine SIGINT?\n"); /* No signal received */

    return 0;
}