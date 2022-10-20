#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_NUM 4
#define BUFFER_SIZE 25
#define READ_END  0
#define WRITE_END 1

/* Example program demonstrating UNIX pipes. (Figures 3.21 & 3.22) */
int main() {
    char write_msg[MSG_NUM][BUFFER_SIZE] = {"Greetings.",
                                            "Studying ",
                                            "Operating Systems ",
                                            "Is Fun!"};
    char read_msg[BUFFER_SIZE];

    pid_t pid;
    int fd[2];

    /* create the pipe */
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    /* now fork a child process */
    pid = fork();

    if (pid < 0) {  /* error occurred */
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) {  /* parent process */
        /* close the unused end of the pipe */
        close(fd[READ_END]);

        /* write to the pipe */
        int write_num;
        for (int i = 0; i < MSG_NUM; i++) {
            write_num = write(fd[WRITE_END], write_msg[i], BUFFER_SIZE);
            printf("Parent has write %d bytes: %s\n", write_num, write_msg[i]);
        }

        /* close the write end of the pipe */
        close(fd[WRITE_END]);

        /* parent will wait for the child to complete */
        wait(NULL);

        printf("Parent terminated.\n");
    } else {  /* child process */
        /* close the unused end of the pipe */
        close(fd[WRITE_END]);

        /* read from the pipe */
        int read_num;
        while ((read_num = read(fd[READ_END], read_msg, BUFFER_SIZE)) > 0) {
            printf("Child read %d bytes: %s\n", read_num, read_msg);
        }

        /* close the read end of the pipe */
        close(fd[READ_END]);

        printf("Child terminated.\n");
    }

    return 0;
}