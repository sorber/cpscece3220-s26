#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {
    int n = 0;
    long halfgb = 1UL << 29UL;

    while (1) {
    	int* p = malloc(halfgb);

        if (p == NULL) {
                printf("malloc failure after %d half GB\n", n);
                return 0;
        }
      	memset(p, 5, halfgb);
        printf ("got %d half GB\n", ++n);
    }
}