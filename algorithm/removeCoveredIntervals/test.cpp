// 本题解决的是：二维数组覆盖的区域，将其删除，返回最后的区间数目
// 覆盖：c <= a 且 b <= d 时，我们才认为区间 [a,b) 被区间 [c,d) 覆盖。
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>

int removeCoveredIntervals(std::vector<std::vector<int>> intervals)
{
  int len = intervals.size();
  int ret = len;

  // 这里找的是符合覆盖的条件
  // 然后直接break，就代表这个区间直接被删除
  for(int i = 0; i < len; i++)
  {
    for(int j = 0; j < len; j++)
    {
      if(i != j && intervals[j][0] <= intervals[i][0] && intervals[i][1] <= intervals[j][1])
      {
        ret--;
        break;
      }
    }
  }
  return ret;
}

int main()
{
  std::vector<std::vector<int>> vv({{1, 4}, {3, 6}, {2, 8}});
  int n = removeCoveredIntervals(vv);
  std::cout <<n << std::endl;
  return 0;
}
