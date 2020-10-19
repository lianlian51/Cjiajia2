// 封装一个UdpSocket类，每一个实例化对象都可以通过成员接口实现一个客户端或服务端
// 也就意味着每个实例化对象都有自己的套接字描述符

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

class UdpSocket{
  private:
    int _socket;
  public:
    UdpSocket();
    bool Socket(); // 创建套接字
    bool Bind(const std::string &ip, const uint16_t port); // 绑定地址信息
    // 接收数据，并且根据默认参数是否为NULL，选择是否获取对端地址信息
    bool Recv(const std::string *buf, std::string *ip = NULL, uint16_t *port = NULL);
    bool Sent(const std::string &data, const std::string &ip, const uint16_t port);
    bool Close(); // 关闭套接字
};

int main()
{
  UdpSocket sock;
  sock.Socket();
  sock.Bind("192.168.122.132", 9000);
  while(1)
  {
    std::string buf;
    sock.Recv(&buf);

    sock.Sent(buf, "192.168.122.132", 8000);
  }
  sock.Close();
}
