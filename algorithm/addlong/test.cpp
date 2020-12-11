// 实现两个字符串数字的相加,最后返回字符串
// 两个很大的数字
// 1.记得每次的vector开辟空间
// 2.字符数字-->数字 只需要 -'0' 即可
// 3.反向赋值时，需要-i和-1

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

std::string AddLongInter(std::string s1, std::string s2)
{
  int size1 = s1.size();
  int size2 = s2.size();

  int size = size1 > size2 ? size1 : size2;

  std::vector<int> v1(size);
  std::vector<int> v2(size);

  for(int i = 0; i < size1; i++)
  {
    v1[i] = s1[size1 - i - 1] -'0';
  }

  for(int i = 0; i < size2; i++)
  {
    v2[i] = s2[size2 - i - 1] - '0';
  }

  std::vector<int> v(size + 1);
  for(int i = 0; i < size; i++)
  {
    v[i] = v1[i] + v2[i];

    if(v[i] > 9)
    {
      v[i + 1] = v[i] / 10;
      v[i] %= 10;
    }
  }

  std::string s;
  if(v[size] == 1)
  {
    for(int i = 0; i < size + 1; i++)
    {
      s +=(v[size - i] + '0');
      // s.push_back(v[size - i] + '0');
      
    }
  }
  else 
  {
    for(int i = 0; i < size; i++)
    {
      s +=(v[size - i - 1] + '0');
      // s.push_back(v[size - i - 1] + '0');
    }
  }

  return s;
}

int main()
{
  std::string s1("54321");
  std::string s2("12345");
  std::cout << AddLongInter(s1, s2) << std::endl;
  return 0;
}
