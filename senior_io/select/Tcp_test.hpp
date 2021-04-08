#pragma once
#include <iostream>
using namespace std;

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
class Tcp
{
  public:
    Tcp()
    {
      sockfd = -1;
    }

    ~Tcp()
    {}

    int CreateSocket()
    {
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if(sockfd < 0)
      {
        perror("sockfd\n");
        return -1;
      }
      return 0;
    }

    int Bind(const string& ip, const uint16_t port)
    {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
      if(ret < 0){
        perror("bind\n");
        return -1;
      }
      return 0;
    }

    int Listen(int backlog = 5)
    {
      int ret = listen(sockfd, backlog);
      if(ret < 0)
      {
        perror("listen\n");
        return -1;
      }
      return 0;
    }

    int Accept(Tcp* ts, struct sockaddr_in* addr, socklen_t* len)
    {
      int ret = accept(sockfd, (struct sockaddr*)addr, len);
      if(ret < 0){
        perror("accept\n");
        return -1;
      }
      ts->SetSocketfd(ret);
      return 0;
    }

    int Recv(string* data)
    {
      char buf[1024] ={0};
      ssize_t ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
      if(ret < 0)
      {
        perror("recv\n");
        return -1;
      }
      else if(ret == 0)
      {
        perror("peer shutdown\n");
        return 0;
      }
      data->assign(buf, strlen(buf));
      return ret;
    }

    int Send(string data)
    {
      ssize_t send_size = send(sockfd, data.c_str(), data.size(), 0);
      if(send_size < 0)
      {
        perror("send\n");
        return -1;
      }
      return send_size;
    }


    int GetSockrtfd()
    {
      return sockfd;
    }

    void SetSocketfd(int fd)
    {
      sockfd = fd;
    }

  private:
  int sockfd;
};
