#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  int fd = open("./linux", O_RDWR | O_CREAT, 0664);
  if(fd < 0)
  {
    return -1;
  }

  printf("fd: %d\n",fd);

  dup2(fd, 1);

  printf("class out\n");
  return 0;
}
