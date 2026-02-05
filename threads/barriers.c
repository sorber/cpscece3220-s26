#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NUMTHREADS 2

pthread_barrier_t mybarrier;


//Thread-local storage --- every thread gets its own copy
//other versions:
//    __thread      - not portable, GCC/CLANG extension
//    thread_local  — C23 version
_Thread_local int thread_id, counter;

void *workerfunc(void *arg) {

    thread_id = gettid();
    
    while (1) {
        printf("%d:\tWAIT!\n", thread_id);
        pthread_barrier_wait(&mybarrier);
        printf("%d:\tGO %d! \n", thread_id, counter++);
        sleep(rand() % 7);
    }
    
    return NULL;
}

int main() {
    pthread_t workers[NUMTHREADS];

    pthread_barrier_init(&mybarrier, NULL, NUMTHREADS+1);

    for (int i=0; i < NUMTHREADS; i++) {
        pthread_create(&workers[i], NULL, workerfunc, NULL);
    }

    for (int i=0; i < 5; i++) {
        printf("main: ready\n");
        pthread_barrier_wait(&mybarrier);
        printf("main: go (%d)!\n",i);
        sleep(7);
    }
    
    return EXIT_SUCCESS;
    
}