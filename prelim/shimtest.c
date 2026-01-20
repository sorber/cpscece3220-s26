
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_NUMBERS 5

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		srand(atoi(argv[1]));
	}

	printf("Let's print %d random numbers...\n", NUMBER_OF_NUMBERS);
	for (int i = 0; i < NUMBER_OF_NUMBERS; i++)
	{
		int r = rand();
		printf("#%d -> %d\n", i, r);
	}
	return 0;
}