// udp客户端通信程序
// 1.创建套接字
// 2.绑定地址信息（不推荐）
// 3.接收数据
// 4.发送数据
// 5.关闭套接字

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h> // socket结构头文件
#include <netinet/in.h> // 地址结构头文件
#include <arpa/inet.h> // 网络字节序转换接口头文件

int main(int argc, char* argv[])
{
  // argc表示运行参数的个数
  // argv存储程序的运行参数，运行参数是运行程序的时候，以空格间隔跟在程序后边
  // ./udp_cli 192.169.*.* 9000
  if(argc != 3)
  {
    printf("usage:./udp_cli 192.169.*.* 9000");
    return -1;
  }
  char* ip = argv[1];
  uint16_t port = atoi(argv[2]);

  // socket(地址域，套接字类型，协议类型)
  int sockfd = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);
  if(sockfd < 0)
  {
    perror("socket perror");
    return -1;
  }
  // bind(套接字描述符，地址信息，地址信息长度)
  struct sockaddr_in addr; // 使用的ipv4的地址结构
  addr.sin_family = AF_INET; // 地址域类型
  addr.sin_port = htons(port); // 网路字节序端口信息-主要使用htons，而不是htonl
  addr.sin_addr.s_addr = inet_addr(ip); // inet_addr将字符串地址转换为网络字节序整型地址
  socklen_t len = sizeof(addr);
  int ret = bind(sockfd, (struct sockaddr*)&addr, len);
  if(ret < 0)
  {
    perror("bind error");
    return -1;
  }
  return 0;

