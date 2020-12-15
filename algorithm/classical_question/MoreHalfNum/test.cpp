// 摩尔投币法

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#if 0
// 方法一：先找到数字出现次数超过一半的数字，然后赋值给num
// 最终再次重新遍历数组，计算数组中等于num的值
// 如果数组中出现num的次数count大于len/2的次数，那么返回num，否则返回0

int MoreHalfNum(std::vector<int> v)
{
  if(v.empty())
  {
    return 0;
  }
  if(v.size() == 1)
  {
    return v[0];
  }

  int count = 1;
  int num = v[0];
  int len = v.size();
  
  for(int  i = 0; i < len; i++)
  {
    if(num == v[i])
    {
      count++;
    }
    else 
    {
      count--;
    }

    if(num != v[i])
    {
      num = v[i];
    }
  }

  count = 0;
  for(int i = 0; i < len; i++)
  {
    if(num == v[i])
      count++;
  }

  return count > (len / 2)? num : 0;
}
#endif

// 方法二：记录count为0的数字，如果遍历到的数字不等于标记的num
// 那么就--，如果相等就++
// 注意：这里的题意说的是多于数组的一半，那么一定存在数字消耗完成之后
//       的那个数字就是出现次数最多的数字

int MoreHalfNum(std::vector<int> v)
{
  int count = 0;
  int num = 0;
  int len = v.size();

  for(int i = 0; i < len; i++)
  {
    if(count == 0)
    {
      num = v[i];
    }

    if(num == v[i])
    {
      count++;
    }
    else 
    {
      count--;
    }
  }
  return num;
}

int main()
{
  std::vector<int> v({1,2,3,2,2,2,5,4,2});
  int num = MoreHalfNum(v);
  std::cout << num << std::endl;
  return 0;
}
