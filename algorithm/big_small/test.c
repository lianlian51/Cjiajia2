// 这里的方法：先找到最大的数字和最小的数字，并且记录其下标
// 然后查找0号位置是不是最小的数，如果不是那么就将最小的数和0号位置的数字交换
// 在查1号位置是不是最大的数字
// 注意：这里的i+=2(因为每次存放的是两个数字)
//
// 如果是我的话，那么我会先排序，然后找对应的数字，填入新的数组即可

#include <stdio.h>
#include <unistd.h>

#define N 10 

void big_small(int num[], int n)
{
  // p代表下标
  int i, j, max, min, pMax, pMin,t;
  for(i = 0; i < n - 1; i += 2)
  {
    max = min = num[i];
    pMax = pMin = i;
    for(j = i + 1; j < n; j++)
    {
      if(max < num[j])
      {
        max = num[j];
        pMax = j;
      }

      if(min > num[j])
      {
        min = num[j];
        pMin = j;
      }
    }
    if(pMin != i)
    {
      t = num[i];
      num[i] = min;
      num[pMin] = t;
      // 如果第一个数字是最大的值，那么交换之后，更新最大值的下标
      if(pMax == i)
        pMax = pMin;
    }
    if(pMax != i + 1)
    {
      t = num[i + 1];
      num[i + 1] = max;
      num[pMax] = t;
    }
  }
}


int main()
{
  int num[N] = {0 ,9, 8, 7, 6, 1, 2, 3, 4, 5};
  for(int i = 0; i < N; i++)
  {
    printf("%d ", num[i]);
  }
  printf("\n");
  big_small(num, N);
  for(int i = 0; i < N; i++)
  {
    printf("%d ", num[i]);
  }
  printf("\n");
  return 0;
}
