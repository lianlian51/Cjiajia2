#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int fd[2];
  int ret = pipe(fd);
  if(ret < 0)
  {
    perror("pipe error!\n");
    return -1;
  }

  // 打印fd[0]和fd[1]的属性
  int flag = fcntl(fd[0], F_GETFL);
  printf("flag-fd[0]:%d\n", flag);

  flag = fcntl(fd[1], F_GETFL);
  printf("flag-fd[1]:%d\n", flag);
  return 0;
}
