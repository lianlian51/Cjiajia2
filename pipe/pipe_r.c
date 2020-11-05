#include <stdio.h>
#include <unistd.h>
#include <string.h>
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
  printf("fd[0]:%d fd[1]:%d\n", fd[0], fd[1]);


#if 0
  // 匿名管道只支持亲缘关系进程间的通信
  int pid = fork();
  if(pid < 0)
  {
    perror("fork error!\n");
    return -1;
  }
  else if(pid == 0)
  {
    // child
    close(fd[0]);
    write(fd[1], "i love you!", 11);
  }
  else if(pid > 0)
  {
    // father
    close(fd[1]);
    char buf[1024] = {0};
    read(fd[0], buf, sizeof(buf) - 1);
    printf("buf:%s\n", buf);
  }
#endif

#if 0
  // 管道读写
  write(fd[1], "i love you!", 11);

  char buf[1024] = {0};
  read(fd[0], buf, sizeof(buf));
  
  printf("buf:%s\n", buf);
  return 0;
#endif
}
