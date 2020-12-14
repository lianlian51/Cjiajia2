// 问题描述：在计算机中，通配符一种特殊语法，广泛应用于文件搜索、数据库、正则表达式等领域。
// 现要求各位实现字符串通配符的算法。
// 要求：
// 实现如下2个通配符：
// *：匹配0个或以上的字符（字符由英文字母和数字0-9组成，不区分大小写。下同） ？：匹配1个字符
//
// 这里只需要处理好*和?就可以了，？直接++
// *：你需要考虑的是0个或更多，这里给了一个标志位，处理了这种情况
//
// 我原来想的是直接在一个循环里面处理*，但是不行,会处理掉一些特殊的情况


#include <iostream>
#include <string>

bool Judge(const std::string& s1, const std::string& s2)
{
  int l1 = s1.size();
  int l2 = s2.size();

  int i = 0, j =0;
  bool flag = false;
  //while(s1[i] || s2[j])
  while(i < l1 || j < l2)
  {
    if(s1[i] == s2[j] || s1[i] == '?')
    {
      i++,j++;
    }
    else if(s1[i] == '*')
    {
      i++;
      flag = true;
    }
    else if(flag)
    {
      while(s1[i] != s2[j])
        j++;
      flag = false;
    }
    else 
    {
      return false;
    }
  }
  //if(s1[i] == '\0' && s2[j] == '\0')
  if(i == l1 && j == l2)
    return true;
  else 
    return false;
}


int main()
{
  std::string s1, s2;
  while(getline(std::cin, s1))
  {
    getline(std::cin, s2);
    if(Judge(s1, s2))
      std::cout << "true" << std::endl << std::endl;
    else 
      std::cout << "false" << std::endl << std::endl;
  }
}
