#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int n = 0;

    while (1) {
        void *p;
        if ((p = malloc(1<<29)) == NULL) {
                printf("malloc failure after %d half GBs\n", n);
                return 0;
        }
        printf ("got %d half GB - %p\n", ++n, p);
    }
}