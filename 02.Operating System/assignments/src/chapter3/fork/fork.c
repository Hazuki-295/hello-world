#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* This program forks a separate process using the fork()/exec() system calls. */
int main() {
    pid_t pid;

    /* fork a child process */
    pid = fork();

    if (pid < 0) {  /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {  /* child process */
        printf("I am the child %d\n", pid);
        execlp("/bin/ls", "ls", NULL);
    } else {  /* parent process */
        printf("I am the parent %d\n", pid);
        wait(NULL);  /* parent will wait for the child to complete */
        printf("Child Complete\n");
    }

    return 0;
}