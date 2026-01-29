#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

#define BIG 10000000000L  //10 billion


void add_up_to_big(uint64_t *subsum) {
	for (uint64_t i = 0; i < BIG; i++) {
		*subsum += i;
	}
}

void * mythreadfunc(void *arg) {
	uint64_t *subsum = (uint64_t*)arg;
	add_up_to_big(subsum);
	return NULL;
}

int main(int argc, char **argv) {
	
	pthread_t t1, t2;
	uint64_t sum1 = 0;
	char dummy[1000];
	uint64_t sum2 = 0;

	pthread_create(&t1, NULL, mythreadfunc, &sum1);
	pthread_create(&t2, NULL, mythreadfunc, &sum2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	printf("The result is %lu\n", sum1 + sum2);
	return 0;
}
