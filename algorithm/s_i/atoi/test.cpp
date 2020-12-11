#include <iostream>
#include <stdlib.h>

// 将字符转化为数字
int main()
{
  int a;
  char buffer[33] = "1234";
  a = atoi(buffer);
  std::cout << a << std::endl;
  return 0;
}
