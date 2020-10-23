#include <iostream>
#include "tcpsocket.hpp"

int main(int argc, char* argv[])
{
  if(argc != 3){
    std::cout << "usage: ./udp_cli ip port\n";
    return -1;
  }
  std::string srv_ip = argv[1];
  uint16_t srv_port = std::stoi(argv[2]);

  TcpSocket cli_sock;
  // 1.创建套接字
  CHECK_RET(cli_sock.Socket());
  // 2.绑定地址信息(不推荐)
  // 3.向服务端发送链接
  CHECK_RET(cli_sock.Connect(srv_ip, srv_port));
  while(1)
  {
    // 4.发送数据
    std::string buf;
    std::cout << "client say : ";
    std::cin >> buf;
    if(cli_sock.Send(buf) == false){
      cli_sock.Close();
      return -1;
    }
    // 5.接收数据
    buf.clear();
    if(cli_sock.Recv(&buf) == false){
      cli_sock.Close();
      return -1;
    }
    std::cout << "server say : " << buf << std::endl;
  }
  // 6.关闭套接字
  cli_sock.Close();
  return 0;
}
