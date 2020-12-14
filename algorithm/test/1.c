#include <stdio.h>
#include <unistd.h>

int main()
{
  int x = 9999;
  int count = 0;
  while(x)
  {
    count++;
    x = x & (x - 1);
  }
  printf("%d\n", count);
}
