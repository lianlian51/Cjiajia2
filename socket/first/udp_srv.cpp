#include "udpsocket.hpp"
#include <iostream>

#define CHECK_RET(q) if((q) == false){return -1;}
int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::cout << "usage: ./udp_srv 192.168.122.132 9000\n";
    return -1;
  }
  std::string ip = argv[1];
  uint16_t port = std::stoi(argv[2]); // c++11的接口

  UdpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Bind(ip, port));
  while(1){
    std::string buf;
    std::string cli_ip;
    uint16_t cli_port;
    if(sock.Recv(&buf, &cli_ip, &cli_port) == false)
    {
      sock.Close();
      return -1;
    }
    std::cout<<"client say: " << buf << std::endl;
    buf.clear();
    std::cout << "server say: ";
    std::cin >> buf;
    if(sock.Sent(buf, cli_ip, cli_port) == false)
    {
      sock.Close();
      return -1;
    }
  }
  sock.Close();
  return 0;
}
