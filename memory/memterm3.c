#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N       10000

int main (void) {
    int i, n = 0;
    char *pp[N];

    long halfgb = 1UL << 29UL;

    for (n = 0; n < N; n++) {
        pp[n] = malloc(halfgb);
        if (pp[n] == NULL)
            break;
    }
    printf("malloced %d half GBs\n", n);

    for (i = 0; i < n; i++) {
        memset (pp[i], 0, halfgb);
        printf("using...%d half GB\n", i+1);
    }

    return 0;
}