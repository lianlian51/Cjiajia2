#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// 将数字转换为字符
// linux下没有itoa，所以我们采用sprintf

int main()
{
  int a = 1234;
  char buffer[33];
  sprintf(buffer, "%d", a);
  std::cout << buffer << std::endl;
  return 0;
}
