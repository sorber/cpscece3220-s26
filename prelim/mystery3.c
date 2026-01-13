#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int add(int a, int b) {
	a++; b--; int result = a+b;
	return result--;
}

int main() {
	int x = 14, y = 3;
	int s = add(x,y++);
	printf("%d %d %d\n",x,y,s);
	return 0;
}