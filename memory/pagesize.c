#include <unistd.h>
#include <stdio.h>

int main()
{
	int ps = getpagesize();

	printf("page size = %d\n", ps);
}
