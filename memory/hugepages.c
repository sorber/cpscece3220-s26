#define _GNU_SOURCE

#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define ONEPAGE 4096
#define ONEGB (1<<20UL)

int main(int argc, char** argv)
{
	
	//mmap(address-hint, size, protections, flags, fd, offset)
	void *onepage = mmap(NULL, ONEPAGE,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    void *onegb = mmap(NULL, ONEGB,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB , -1, 0);

    //madvise(onegb, ONEGB, MADV_HUGEPAGE);
	printf("small =\t%p\nlarge =\t%p\n",onepage, onegb);

}
