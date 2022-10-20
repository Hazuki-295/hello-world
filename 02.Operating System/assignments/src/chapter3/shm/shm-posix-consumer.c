#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

/*
 * Simple program demonstrating shared memory in POSIX systems.
 * This is the consumer process. (Figure 3.17)
 */

int main() {
    const int SIZE = 4096;
    const char *name = "OS";

    /* shared memory file descriptor */
    int shm_fd;
    /* pointer to shared memory segment */
    void *ptr;

    /* open the shared memory segment */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        printf("Shared memory failed\n");
        exit(-1);
    }

    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }

    /* read from the shared memory region */
    printf("%s", (char *) ptr);

    /* remove the shared memory segment */
    if (shm_unlink(name) == -1) {
        printf("Error removing %s\n", name);
        exit(-1);
    }

    return 0;
}