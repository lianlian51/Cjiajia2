#include <stdio.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

int main()
{
  // 1.创建套接字
  int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(fd < 0)
  {
    perror("socket error\n");
    return -1;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("192.168.67.128");
  addr.sin_port = htons(19999);

  // 2.绑定地址信息（不推荐）
  while(1)
  {
    std::string s;
    std::cin >> s;
    // 3.发送数据
    ssize_t ret = sendto(fd, s.c_str(), sizeof(s), 0, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
      perror("sendto error\n");
      continue;
    }
    // 4.接收数据
    char buf[1024] = {0};
    ret = recvfrom(fd, buf, sizeof(buf) - 1, 0, NULL, NULL);
    if(ret < 0)
    {
      perror("recvfrom error\n");
      continue;
    }
    printf("srv say: %s\n", buf);
  }
  // 5.关闭套接字
  close(fd);
  return 0;
}
