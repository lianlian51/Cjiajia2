#include <stdio.h>
#include <unistd.h>

int main()
{
  int fd[2];
  int ret = pipe(fd);
  if(ret < 0)
  {
    perror("pipe error!\n");
    return -1;
  }
  printf("fd[0]:%d\n", fd[0]);
  printf("fd[1]:%d\n", fd[1]);

  int count = 0;
  while(1)
  {
    write(fd[1], "h", 1);
    count++;
    printf("count:%d\n", count);
  }
  return 0;
}
