#include <stdio.h>


int main() {
    for (int i=1; i < 18; ++i) {
        printf("%d -> %d\n", i, __builtin_clz(i));
    }
}