#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

uint64_t findMaxPowOf10(uint64_t num) {
    uint64_t rval = 1;
    while(num) {
        rval *= 10;
        num /= 10;
    }
    return rval;
}

void printptr(void * p)
{
	uint64_t num = (uint64_t) p;
	uint64_t pow10 = findMaxPowOf10((uint64_t)num);

	while(pow10) {
	    uint64_t digit = num / pow10;
	    char dig_char = digit+'0';
	    write(STDOUT_FILENO, &dig_char,1);
	    num -= digit * pow10;
	    pow10 /= 10;
	}
	write(STDOUT_FILENO, "\n",1);

}

#define INCREMENT 4096

int main()
{
	void *p = sbrk(0); //get the current break
	printptr(p);

	void *p2 = sbrk(INCREMENT);  //increments the program break, and return the previous break
	void *n = sbrk(0); //get the current break.

	printptr(p2);
	printptr(n);
	printptr(p2+INCREMENT);

	//I can now write to n
	int *intptr = n-10;
	*intptr = 257;

	brk(p2); //decrement the program break ("unmapping" the memory) 
	void *p4 = sbrk(0);

	printptr(p4);

	//what if I try to write to that old address?
	*intptr = 12345;

	return 0;
}
