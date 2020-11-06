#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid = fork();
  if(pid < 0)
  {
    perror("fork");
    exit(1);
  }
  if(pid == 0)
  {
    printf("child is run.child pid is %d\n", getpid()); // getpid获得当前进程
    sleep(5);
    exit(10);
  }
  if(pid > 0)
  {
    int status = 0;
    pid_t ret = waitpid(-1, &status, 0);
    printf("this is for test wait.\n");
    if(WIFEXITED(status)&&(ret == pid))
    {
      printf("child is 5s success.child exit code is :%d\n",WEXITSTATUS(status));
    }else if (ret > 0)
    {
      printf("wait child failed.\n");
      exit(1);
    }
  }
  return 0;
}
// 阻塞式等待：父进程等待子进程退出，然后执行自己
