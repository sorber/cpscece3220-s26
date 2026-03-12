#include <stdio.h>
#include <unistd.h>

int x = 0;

int main()
{
  if (fork()==0)
    x = 2;
  printf("Hello World. x = %d (%p)\n", x, &x);
}
