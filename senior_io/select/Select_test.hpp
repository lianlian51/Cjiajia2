#pragma once 
#include "Tcp_test.hpp"

#include <vector>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>

class Select
{
  public:
    Select()
    {
      FD_ZERO(&readfs);
      nfds = -1;
    }

    ~Select()
    {}

    void Add(int fd)
    {
      FD_SET(fd, &readfs);
      if(fd > nfds){
        nfds = fd;
      }
    }

    void Deletefd(int fd)
    {
      FD_CLR(fd, &readfs);
      for(int i = nfds; i >= 0; --i)
      {
        if(FD_ISSET(i, &readfs) == 0)
        {
          continue;
        }
        nfds = i;
        break;
      }
    }

    int SelectWait(struct timeval* tv, std::vector<Tcp>* vec)
    {
      fd_set tmp = readfs;
      int ret = select(nfds + 1, &tmp, NULL, NULL, tv);
      if(ret < 0)
      {
        perror("select\n");
        return -1;
      }
      else if(ret == 0)
      {
        printf("time out..\n");
        return 0;
      }

      for(int i = 0; i < nfds + 1; ++i)
      {
        if(FD_ISSET(i, &tmp) == 1)
        {
          Tcp ts;
          ts.SetSocketfd(i);

          vec->push_back(ts);
        }
      }
      return ret;
    }

  private:
    // 读时间集合
    fd_set readfs;
    // 轮询范围
    int nfds;
};
