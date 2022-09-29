#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXBUF 8192  /* Max I/O buffer size */

void sigchld_handler1(int sig) {
    waitpid(-1, NULL, 0);  /* WARNING: This code is buggy! */
    printf("Handler reaped child\n");
    sleep(1);
}

/* Modify the SIGCHLD handler to reap as many zombie children as possible each time */
void sigchld_handler2(int sig) {
    while (waitpid(-1, NULL, 0) > 0) {
        printf("Handler reaped child\n");
    }
    sleep(1);
}

int main() {
    char buf[MAXBUF];

    // signal(SIGCHLD, sigchld_handler1);
    signal(SIGCHLD, sigchld_handler2);

    /* Parent creates children */
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            printf("Hello from child %d\n", (int) getpid());
            exit(0);
        }
    }

    /* Parent waits for terminal input and then processes it */
    fgets(buf, MAXBUF, stdin);

    printf("Parent processing input\n");
    while (1);

    exit(0);
}