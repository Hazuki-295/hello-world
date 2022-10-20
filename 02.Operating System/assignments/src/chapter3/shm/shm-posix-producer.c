#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

/*
 * Simple program demonstrating shared memory in POSIX systems.
 * This is the producer process that writes to the shared memory region. (Figure 3.16)
 */

int main() {
    const int SIZE = 4096;
    const char *name = "OS";
    const char *message0 = "Studying ";
    const char *message1 = "Operating Systems ";
    const char *message2 = "Is Fun!\n";

    /* shared memory file descriptor */
    int shm_fd;
    /* pointer to shared memory segment */
    void *ptr;

    /* create the shared memory segment */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configure the size of the shared memory segment */
    if (ftruncate(shm_fd, SIZE) == -1) {
        printf("Truncate failed\n");
        exit(-1);
    }

    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }

    /* write to the shared memory region */
    sprintf(ptr, "%s", message0);
    ptr += strlen(message0);
    sprintf(ptr, "%s", message1);
    ptr += strlen(message1);
    sprintf(ptr, "%s", message2);
    ptr += strlen(message2);

    return 0;
}