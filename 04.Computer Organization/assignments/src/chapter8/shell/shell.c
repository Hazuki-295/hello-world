#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAXLINE 8192 /* Max text line length */
#define MAXARGS 128  /* Max argument number */

extern char **environ; /* Defined by libc */

/* Function prototypes */
void eval(const char *cmdline); // Evaluate a command line
int parseline(char *buffer, char *argv[]); // Parse the command line
int builtin_command(char *argv[]);

void unix_error(char *msg);

int main() {
    char cmdline[MAXLINE]; /* Command line */
    while (1) {
        /* Print a command-line prompt */
        printf("> ");

        /* Read: read a command line from the user */
        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin)) {
            exit(0);
        }
        /* Evaluate: parse the space-separated command line and run programs */
        eval(cmdline);
    }
}

/* eval - Evaluate a command line */
void eval(const char *cmdline) {
    char *argv[MAXARGS];  /* Argument list execve() */
    char buffer[MAXLINE]; /* Holds modified command line */
    int background;       /* Should the job run in background or foreground? */
    pid_t pid;            /* Process id */

    strcpy(buffer, cmdline);
    background = parseline(buffer, argv);
    if (argv[0] == NULL) {  /* Ignore empty lines */
        return;
    }

    if (!builtin_command(argv)) {
        if ((pid = fork()) == 0) {  /* Child runs user job */
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        /* Parent waits for foreground job to terminate */
        if (!background) {
            int status;
            if (waitpid(pid, &status, 0) < 0)
                unix_error("error: waitpid error");
        } else {
            printf("%d %s", pid, cmdline);
        }
    }
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) {
    if (!strcmp(argv[0], "quit")) /* quit command */
        exit(0);
    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
        return 1;
    return 0;                     /* Not a builtin command */
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
    if (argc == 0) {
        return 1;
    }

    /* Should the job run in the background? */
    if ((background = (*argv[argc - 1] == '&'))) {
        argv[--argc] = NULL; /* Remove argument & */
    }
    return background;
}

void unix_error(char *msg) {  /* Unix-style error */
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}