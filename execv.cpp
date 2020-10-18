#include <stdio.h>
#include <unistd.h>

int main()
{
  char* arg[] = {"ls", "-a", "-l","/", NULL };
  execv("/bin/ls",arg);
  printf("hello world!\n");
  return 0;
}
