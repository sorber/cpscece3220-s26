#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

#define BIG 2000000000L	 //2 Billion

uint64_t counter = 0;

// do something CPU-bound
void count_to_big() {
	printf("Counting rapidly...\n");
	for (uint64_t i = 0; i < BIG; i++) {
		counter++;
	}
	printf("Counting rapidly...done\n");
}

// do something
void do_something_really_slow(int id) {
	for (int i = 0; i < 10; i++) {
		printf("(%d)\tCounting slowly...%d\n", id, i);
		sleep(1);
	}
}

void *tfunc(void *param) {
	int *id = param;
	//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	do_something_really_slow(*id);
	free(id);
	return NULL;
}

#define NUMTHREADS 3

int main(int argc, char **argv) {
	pthread_t threads[NUMTHREADS];
	for (int i=0; i < NUMTHREADS; i++) {
		int *tid = malloc(sizeof(int));
		*tid = i;
		pthread_create(&threads[i], NULL, tfunc, tid);
	}
	count_to_big();

	pthread_cancel(threads[0]);

	for (int i=0; i < NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	
	printf("\nCounter=%lu\n", counter);
	return 0;
}
