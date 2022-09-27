#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    char *pwd = getenv("PWD");
    if (pwd != NULL) {
        printf("Print working directory:\n");
        printf("    %s\n\n", pwd);
    }

    printf("Command-line arguments: (argc = %d)\n", argc);
    for (int i = 0; argv[i] != NULL; i++) {
        printf("    argv[%2d]: %s\n", i, argv[i]);
    }

    printf("\n");

    printf("Environment variables:\n");
    for (int i = 0; envp[i] != NULL; i++) {
        printf("    envp[%2d]: %s\n", i, envp[i]);
    }

    exit(0);
}
