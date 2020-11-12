#include <iostream>
#include "tcpsocket.hpp"

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::cout << "usage : ./udp_srv ip port\n";
    return -1;
  }

  std::string ip = argv[1];
  uint16_t port = std::stoi(argv[2]);

  TcpSocket lst_sock; // 实例化监听套接字--用于获取新连接
  // 1.创建套接字
  CHECK_RET(lst_sock.Socket());
  // 2绑定地址信息
  CHECK_RET(lst_sock.Bind(ip, port));
  // 3.开始监听---服务端千万不要把这一步忘了
  CHECK_RET(lst_sock.Listen());
  while(1)
  {
    // 4.获取新建连接的套接字 -- 服务端有可能与多个客户端通信，所以要多次新建连接
    TcpSocket new_sock;
    if(lst_sock.Accept(&new_sock) == false){
      continue; // 服务端不能因为获取一次新建连接失败而退出
    }
    // 5.通过新建连接套接字接收数据
    std::string buf;
    if(new_sock.Recv(&buf) == false)
    {
      new_sock.Close();
      continue;
    }
    std::cout << "client say : " << buf << std::endl;
    // 6.停过新建连接套接字发送数据
    buf.clear();
    std::cout << "server say : ";
    std::cin >> buf;
    if(new_sock.Send(buf) == false){
      new_sock.Close();  // 一个客户端通信出现问题，不应该退出服务端，而是和下一个客户端进行通信
      continue;
    }
  }
  // 7.关闭连接
  lst_sock.Close();
  return 0;
}
