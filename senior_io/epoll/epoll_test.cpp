#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>

/*
 1.创建epoll操作句柄
 2.添加事件结构到epoll的红黑树中
    2.1 准备事件结构
    2.2 关心的事件以及文件描述符
 3.监控
    3.1 阻塞
    3.2 非阻塞
    3.3 带有超时时间
 4.判断epoll_wait的返回值
 5.执行相应的操作
 */

int main()
{
  int epfd = epoll_create(5);
  if(epfd < 0){
    perror("epoll_create");
    return 0;
  }

  struct epoll_event ee;
  ee.events = EPOLLIN;
  ee.data.fd = 0;
  epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &ee);

  while(1)
  {
    struct epoll_event arr[10];
    memset(arr, '\0', sizeof(struct epoll_event)*10);
    int ret = epoll_wait(epfd, arr, 10, 5000);
    if(ret < 0){
      perror("epoll_wait\n");
      return 0;
    }
    else if(ret == 0)
    {
      printf("timeout\n");
      continue;
    }

    for(int i = 0; i < 10; i++)
    {
      if(arr[i].events == EPOLLIN)
      {
        char buf[1024] = {0};
        read(arr[i].data.fd, buf, sizeof(buf) - 1);

        printf("buf:%s", buf);
      }
    }
  }
  return 0;
}
