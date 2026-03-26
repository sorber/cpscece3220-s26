#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define LENGTH (1UL << 20) // 1 MB
#define HUGE_LENGTH (2UL << 20) // 2 MB
#define HUGE_PAGE_SIZE (2UL << 20) // 2 MB

int main() {
    void *ptr;

    // Allocate memory using normal pages
    ptr = mmap(NULL, LENGTH, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Write to memory using normal pages
    sprintf((char *) ptr, "Hello, world!");
    printf("%s (%p)\n", (char *) ptr, ptr);

    // Allocate memory using huge pages
    ptr = mmap(NULL, HUGE_LENGTH, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Write to memory using huge pages
    sprintf((char *) ptr, "Hello, huge pages!");
    printf("%s (%p)\n", (char *) ptr, ptr);

    // Free memory
    munmap(ptr, HUGE_LENGTH);
    munmap(ptr, LENGTH);

    return EXIT_SUCCESS;
}
