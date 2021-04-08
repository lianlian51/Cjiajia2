#include "Tcp_test.hpp"
#include "Select_test.hpp"

#include <stdlib.h>
#define CHEACK(p) if(p < 0) {return 0;}


int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    printf("sage ./Tcpsvr [ip] [port]\n");
    return 0;
  }
  string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  Tcp ts;
  CHEACK(ts.CreateSocket());
  CHEACK(ts.Bind(ip, port));
  CHEACK(ts.Listen());

  Select ss;
  ss.Add(ts.GetSockrtfd());

  while(1)
  {
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    vector<Tcp> vec;
    int ret = ss.SelectWait(&tv, &vec);
    if(ret < 0)
    {
      perror("select \n");
      return -1;
    }
    else if(ret == 0){
      // 时间耗尽
      continue;
    }

    // 通信
    // 1.辨别是监听套接字还是普通的套接字
    // 2.收发数据
    //
    int l = vec.size();
    for(int i = 0; i < l; ++i)
    {
      if(vec[i].GetSockrtfd() == ts.GetSockrtfd())
      {
        // 监听套接字
        // 建立新连接
        cout << "begin Listen...\n" << endl;
        Tcp new_sock;
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        ts.Accept(&new_sock, &addr, &len);

        printf("new sockfd: %d; peer_ip: %s; peer_port: %d\n", new_sock.GetSockrtfd(), inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        ss.Add(new_sock.GetSockrtfd());
      }
      else 
      {
        // 新连接
        Tcp new_sock_tcp = vec[i];
        string data;
        data.clear();
        int ret = new_sock_tcp.Recv(&data);
        if(ret < 0)
        {
          perror("recv \n");
          close(new_sock_tcp.GetSockrtfd());
          ss.Deletefd(new_sock_tcp.GetSockrtfd());
          continue;
        }
        else if(ret == 0)
        {
          close(new_sock_tcp.GetSockrtfd());
          ss.Deletefd(new_sock_tcp.GetSockrtfd());
        }

        cout << data << endl;
        
        string send_data; // = "i am server";
        cin >> send_data;
        new_sock_tcp.Send(send_data);
      }
    }
  }
  close(ts.GetSockrtfd());
  return 0;
}
