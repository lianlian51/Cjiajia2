#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  int ret = mkfifo("./fifo_test", 0664);
  if(ret < 0)
  {
    perror("mkfifo error!\n");
    return -1;
  }
  // todo
 
  int fd;
  char buf[] = "hello!\n";
  fd = open("./fifo_test", O_RDWR);
  // write
  write(fd, buf, sizeof(buf));
  
  char _buf[1024] = {0};
  read(fd, _buf, sizeof(_buf));

  printf("_buf:%s\n", _buf);
  // read
  return 0;
}
