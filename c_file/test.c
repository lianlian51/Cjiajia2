#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int fd = open("./linux2", O_RDWR | O_CREAT, 0664); // 系统调用接口
  if(fd < 0)  // 调用失败
  {
    perror("open");
    return -1;
  }
  // O_RDWR 和 O_CREAT 都是宏 
  printf("%d\n", O_RDWR | O_CREAT);
  printf("fd : %d\n", fd); // 文件描述符fd_array的下标

  write(fd, "class out", 9);

  lseek(fd, 0, SEEK_SET);

  char buf[1024] = {0};
  read(fd, buf, sizeof(buf) -1);

  printf("buf-%s\n", buf);
  close(fd);
  return 0;
}
