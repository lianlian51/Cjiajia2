// 二分查找的延伸解决方法（这里是找大于等于）
// 这是要找的内容是第一个大于等于传入的值val的第几个值
// 如果没有找到的话就返回数组的长度n+1
// 对于STL的接口以及cin，cout这些在linux加上std命名空间

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>

int upper_bond_(int val_, std::vector<int> vec_)
{
  // n:数组的长度，left：数组左边的下标，right：数组右边的下标
  int n = vec_.size();
  int left = 0;
  int right = n - 1;
  while(left <= right)
  {
    // mid是中间的下标
    int mid = (left + right) / 2;

    // 相等的话那么判断前一个是不是val
    // 不是的话那么就返回，是的话那么就将right = mid - 1
    if(vec_[mid] == val_)
    {
      if(mid == 0 || vec_[mid - 1] != val_)
      {
        return mid + 1;
      }
      else 
      {
        right = mid - 1;
      }
    }
    else if(vec_[mid] > val_) 
    {
      // 这里大于val的值，前一个数字小于val的话
      // 那么就返回，不是的话就更新right = mid - 1
      if(mid == 0 || vec_[mid - 1] < val_)
      {
        return mid + 1;
      }
      right = mid - 1;
    }
    else if(vec_[mid] < val_)
    {
      // 小于val的就直接更新left = mid + 1
      left = mid + 1;
    }
  }
  return n + 1;
}

int main()
{
  // 测试数组
  std::vector<int> v{1, 2, 4, 4, 5};
  // 4:要查找的数字  v:要在这个数组查找 
  int num = upper_bond_(4, v);
  std::cout << num << std::endl;
  return 0;
}
