#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigback(int signo)
{
  printf("signo :%d\n", signo);
}

int main()
{
  signal(2, sigback);
  while(1)
  {
    printf("linux so easy!\n");
    sleep(1);
  }
  return 0;
}
