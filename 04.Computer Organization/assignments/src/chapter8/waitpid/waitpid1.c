#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define N 10

void unix_error(char *msg);

int main() {
    pid_t pid;

    /* Parent creates N children */
    for (int i = 0; i < N; i++) {
        if ((pid = fork()) == 0) {  /* Child */
            exit(100 + i);
        }
    }

    /* Parent reaps N children in no particular order */
    int status;
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n",
                   pid, WEXITSTATUS(status));
        } else {
            printf("child %d terminated abnormally\n", pid);
        }
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD) {
        unix_error("waitpid error");
    }

    exit(0);
}

void unix_error(char *msg) {  /* Unix-style error */
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}