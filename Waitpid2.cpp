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
  if(pid==0)
  {
    printf("child is run. child pid is :%d\n",getpid());
    sleep(5);
    printf("child is run.\n");
    exit(10);
  }
  if(pid > 0)
  {
    int status = 0;
    pid_t ret = 0;
    do{
      ret = waitpid(-1,&status, WNOHANG);// 非阻塞式等待
      if(ret == 0)
      {
        printf("child is running.\n");
      }
      sleep(1);
    }while(ret == 0); // ret != 0表示子进程结束
    if(WIFEXITED(status)&&(ret == pid))
    {
      printf("wait child 5s success.child exit code is :%d\n",WEXITSTATUS(status));
    }else{
      printf("wait child falied.\n");
      exit(1);
    }
  }
  return 0;
}
