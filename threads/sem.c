#include <time.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdint.h>

#define NUM_THREADS 30
#define NUM_BUFFERS 5
#define ITERATIONS 31

sem_t empty_semaphore;
sem_t full_semaphore;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int front = 0;
int back = 0;
char *buffer[NUM_BUFFERS];
int done = 0;

void *consumer_func(void *arg)
{
	int id = (uintptr_t)arg;

	while (!done)
	{
		printf("[%d] waiting\n", id);

		// wait for a buffer to be full
		sem_wait(&full_semaphore);

		if (done)
			break;

		char *thebuf;
		int oldback;

		pthread_mutex_lock(&mutex);
		thebuf = buffer[back];
		buffer[back] = NULL;
		oldback = back;
		back = (back + 1) % NUM_BUFFERS;
		pthread_mutex_unlock(&mutex);
		sleep(1); // for dramatic effect

		printf("[%d] consume @(%d) -- %s\n", id, oldback, thebuf);
		free(thebuf);

		// signal producer that there is now room
		sem_post(&empty_semaphore);
	}
	printf("[%d] consumer done\n", id);
	return NULL;
}

void *producer_func(void *arg)
{
	sleep(2); // for dramatic effect
	for (int i = 0; i < ITERATIONS; i++)
	{
		// wait for a buffer to be available
		sem_wait(&empty_semaphore);

		pthread_mutex_lock(&mutex);
		// produce another message
		buffer[front] = malloc(1024);
		sprintf(buffer[front], "message %d", i);
		printf("producing @(%d) -- %s\n", front, buffer[front]);
		front = (front + 1) % NUM_BUFFERS;
		pthread_mutex_unlock(&mutex);

		sem_post(&full_semaphore);
	}
	done = 1;
	return NULL;
}

int main()
{
	// initialize my_semaphore,
	//	no sharing,
	//	initial value of SEM_INIT_VALUE
	sem_init(&empty_semaphore, 0, NUM_BUFFERS);
	sem_init(&full_semaphore, 0, 0);

	pthread_t consumers[NUM_THREADS];
	pthread_t producer;

	// create the consumers
	for (long i = 0; i < NUM_THREADS; i++)
	{
		pthread_create(&consumers[i], NULL,
					   consumer_func, (void *)i);
	}

	pthread_create(&producer, NULL, producer_func, NULL);
	// wait for completion
	pthread_join(producer, NULL);

	// signal remaining waiters
	for (int i = 0; i < NUM_THREADS; i++)
	{
		sem_post(&full_semaphore);
	}
	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(consumers[i], NULL);
	}
}
