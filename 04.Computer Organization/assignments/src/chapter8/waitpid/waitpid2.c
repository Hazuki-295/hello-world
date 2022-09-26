#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define N 10

void unix_error(char *msg) {  /* Unix-style error */
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        unix_error("Fork error");
    }
    return pid;
}

int main() {
    int status, i;
    pid_t pid[N], retpid;

    /* Parent creates N children */
    for (i = 0; i < N; i++) {
        if ((pid[i] = Fork()) == 0) {  /* Child */
            exit(100 + i);
        }
    }

    /* Parent reaps N children in order */
    i = 0;
    while ((retpid = waitpid(pid[i++], &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n",
                   retpid, WEXITSTATUS(status));
        } else {
            printf("child %d terminated abnormally\n", retpid);
        }
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD) {
        unix_error("waitpid error");
    }

    exit(0);
}