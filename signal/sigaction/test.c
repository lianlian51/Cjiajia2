#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigback(int signo)
{
  printf("signo: %d\n", signo);
}

int main()
{
  // act--->入参
  struct sigaction act;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  act.sa_handler = sigback;

  // old--->出参
  struct sigaction oldact;
  sigaction(2, &act, &oldact);

  getchar();

  sigaction(2, &oldact, NULL);

  while(1)
  {
    printf("linux so easy!\n");
    sleep(1);
  }
  return 0;
}
