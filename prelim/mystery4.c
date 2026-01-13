#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef int (*afun)(int);

int x(int b) { return b - 1; }
int y(int b) { return b + 3; }
int z(int b) { return b * 2; }

int cmp(afun f1, int (*f2)(int), int a) {
	return f1(f2(a));
}

int main() {
	printf("%d\n", z(cmp(x, y, 1)));
	printf("%d\n", y(cmp(z, x, 3)));
	return 0;
}
