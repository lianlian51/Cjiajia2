#include <stdio.h>
#include <unistd.h>

int main(int argc , char* argv[])
{
  execvp("ls",arg);
  printf("hello world!\n");
  return 0;
}
