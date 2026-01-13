#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_VALS 5
#define OFFSET 2
#define NUM_TO_COPY 3

int main()
{
	int *v1 = malloc(sizeof(int) * MAX_VALS);
	int *v2 = malloc(sizeof(int) * MAX_VALS);
	int i;
	for (i=0; i < MAX_VALS; i++)
	{ v1[i] = i << 1; }

	memcpy(v2,v1+OFFSET,sizeof(int)*NUM_TO_COPY);
	printf("%d %d %d %d %lu\n",v2[0],v2[1],v2[2],v2[3], sizeof(v1));
	return 0;
}