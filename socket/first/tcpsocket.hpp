#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/socket.h>  // 套接字接口头文件
#include <arpa/inet.h>  // 字节序转换头文件
#include <netinet/in.h> // 地址结构头文件


#define MAX_LISTEN 10
#define CHECK_RET(q) if((q) == false) {return -1;}
class TcpSocket{
private:
  int _sockfd;
public:
  TcpSocket():_sockfd(-1) {}
  bool Socket()
  {
    _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(_sockfd < 0)
    {
      perror("socket error");
      return false;
    }
    return true;
  }
  bool Bind(const std::string &ip, uint16_t port)
  {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(addr);
    if(bind(_sockfd, (struct sockaddr*)&addr, len) < 0)
    {
      perror("bind error");
      return false;
    }
    return true;
  }
  bool Listen(int backlog = MAX_LISTEN)
  {
    // int listen(in sockfd, int backlog);
    if(listen(_sockfd, backlog) < 0)
    {
      perror("listen error");
      return false;
    }
    return true;
  }

  bool Connect(const std::string &ip, uint16_t port)
  {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(addr);
    // connect(描述符， 服务端地址信息，地址信息长度)
    if(connect(_sockfd, (struct sockaddr*)&addr, len) < 0)
    {
      perror("connet error");
      return false;
    }
    return true;
  }

  bool Accept(TcpSocket *sock, std::string *ip = NULL, uint16_t *port = NULL)
  {
    // int accept(int sockfd, struct sockaddr *cli_addr, socklen_t *len)
    struct sockaddr_in cli_addr;
    socklen_t len = sizeof(cli_addr);
    int newfd = accept(_sockfd, (struct sockaddr*)&cli_addr, &len);
    if(newfd < 0)
    {
      perror("accept error");
      return false;
    }
    if(ip != NULL)
    {
      *ip = inet_ntoa(cli_addr.sin_addr);
    }
    if(port != NULL)
    {
      *port = ntohs(cli_addr.sin_port);
    }
    sock->_sockfd = newfd; // 将新建连接的描述符，赋值给传入的TCPSocket对象
    return true;
  }

  bool Recv(std::string *buf)
  {
    // recv(描述符，缓冲区，接收数据长度，标志位)
    char tmp[1024] = {0};
    int ret = recv(_sockfd, tmp, 1024, 0);
    if(ret < 0)
    {
      perror("recv error");
    }else if(ret == 0)
    {
      printf("connection shutdown");
      return false;
    }
    buf->assign(tmp, ret);
    return true;
  }

  bool Send(const std::string &data)
  {
    // send(描述符，要发送的数据，数据的长度，标志位)
    int ret = send(_sockfd, data.c_str(), data.size(), 0);
    if(ret < 0)
    {
      perror("send error");
      return false;
    }
    return true;
  }

  bool Close()
  {
    if(_sockfd >= 0)
    {
      close(_sockfd);
      _sockfd = -1;
    }
    return true;
  }
};
