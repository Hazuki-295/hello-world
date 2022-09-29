#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 8192 /* Max text line length */
#define MAXARGS 128  /* Max argument number */

extern char **environ;           /* Defined by libc */
volatile sig_atomic_t pid;       /* global variable pid */
volatile sig_atomic_t pid_fore;
volatile sig_atomic_t pid_back;

/* Function prototypes */
void eval(const char *cmdline); // Evaluate a command line
int parseline(char *buffer, char *argv[]); // Parse the command line

void sigchld_handler(int sig) { /* SIGCHLD handler, reap the children */
    int status;
    pid = waitpid(-1, &status, 0);
    if (WIFEXITED(status)) {
        if (pid == pid_fore) {
            printf("Message: %d Foreground job done\n", pid_fore);
        } else if (pid == pid_back) {
            printf("Message: %d Background job done\n", pid_back);
        }
    }
}

void sigint_handler(int sig) { /* SIGINT handler */
    printf("\nHave a nice day!\n");
    _exit(0);
}

int main() {
    char cmdline[MAXLINE]; /* Command line */

    signal(SIGCHLD, sigchld_handler);  /* Install signal handlers */
    signal(SIGINT, sigint_handler);

    while (1) {
        /* Print a command-line prompt */
        printf("> ");

        /* Read: read a command line from the user */
        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin)) {
            printf("\nCompleted.\n");
            exit(0);
        }
        /* Evaluate: parse the space-separated command line and run programs */
        eval(cmdline);
    }
}

/* parseline - Parse the command line and build the argv array */
int parseline(char *buffer, char **argv) {
    char *start = buffer; /* Points to start index of the token */
    char *delim;          /* Points to first space delimiter */
    int argc = 0;         /* Number of args */
    int background;       /* Background job? */

    buffer[strlen(buffer) - 1] = ' '; /* Replace trailing '\n' with space */
    while (start && (*start == ' ')) {  /* Ignore leading spaces */
        start++;
    }

    /* Build the argv list */
    while ((delim = strchr(start, ' '))) {
        argv[argc++] = start;
        *delim = '\0';
        start = delim + 1;
        while (start && (*start == ' ')) {  /* Ignore spaces */
            start++;
        }
    }
    argv[argc] = NULL;  /* Terminate the argv array */

    /* Ignore blank line, because of the following reference *argv[argc - 1] */
    if (argc == 0) return 0;

    /* Should the job run in the background? */
    if ((background = (*argv[argc - 1] == '&'))) {
        argv[--argc] = NULL; /* Remove argument & */
    }
    return background;
}

void execute(const char *filename, char *argv[], int background) {
    sigset_t mask, prev;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);

    sigprocmask(SIG_BLOCK, &mask, &prev);  /* Block SIGCHLD */
    if ((pid = fork()) == 0) {  /* Child runs user job */
        if (execve(filename, argv, environ) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(0);
        }
    }

    /* Parent */
    sigprocmask(SIG_SETMASK, &prev, NULL);  /* Unblock SIGCHLD */
    if (!background) {
        pid_fore = pid;
        pid = 0;
        while (!pid) {
            sigsuspend(&prev);  /* waits for foreground job to terminate */
        }
    } else {
        pid_back = pid;
        printf("[1] %d %s\n", pid_back, argv[0]);
    }
}

/* eval - Evaluate a command line */
void eval(const char *cmdline) {
    char *argv[MAXARGS];  /* Argument list execve() */
    char buffer[MAXLINE]; /* Holds modified command line */
    int background;       /* Should the job run in background or foreground? */

    strcpy(buffer, cmdline);
    background = parseline(buffer, argv);
    if (argv[0] == NULL || !strcmp(argv[0], "&")) {  /* Ignore empty lines and singleton & */
        return;
    }

    if (!strcmp(argv[0], "quit")) {  /* quit command */
        printf("Good bye\n");
        exit(0);
    }

    char builtin[MAXLINE] = "/bin/";
    if (access(strcat(builtin, argv[0]), F_OK) == 0) {  /* If first arg is a builtin command */
        execute(builtin, argv, background);
    } else {
        execute(argv[0], argv, background);
    }
}