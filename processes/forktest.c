

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    printf("before\n");
    pid_t p = fork();
    if (p == 0) {
        printf("I'm a child!\n");
    } else {
        printf("I'm a parent!\n");
    }
    printf("after %d\n", p);
}