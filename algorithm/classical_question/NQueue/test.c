#include <stdio.h>
#include <unistd.h>

int place[8]; // 放置皇后
int flag[8];  // 标记已经放过的列
int d1[15]={0}; // 主对角线的差值相等，有负数的情况，所以要加7
int d2[15]={0}; // 次对角线的和相等
int count_ = 0; // 计算成功摆放的次数


void Print()
{
  int i;
  printf("第%d中方法\n", ++count_);
  for(i = 0; i < 8; i++)
  {
    printf("(%d, %d)\n",i, place[i]);
  }
  printf("\n");
}

void Print_()
{
  printf("第%d中方法\n", ++count_);
  printf("-----------------------------\n");
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(j == 0)
        printf("|");
      else if(place[i] == j)
        printf(" Q |");
      else 
        printf("   |");
    }
    printf("\n");
  }
  printf("-----------------------------\n");
  printf("\n");
}
void search(int k) // k:代表行
{
  for(int i = 0; i < 8; i++) // 代表列
  {
    if(flag[i] == 0 && d1[k - i + 7] == 0 && d2[k + i] == 0)
    {
      place[k] = i;
      flag[i] = 1;
      d1[k - i + 7] = 1;
      d2[k + i] = 1;
      if(k == 7)
      {
        Print_();
      }
      else
      {
        search(k + 1);
      }
      flag[i] = 0;
      d1[k - i + 7] = 0;
      d2[k + i] = 0;
    }
  }
}


int main()
{
  search(0);
  return 0;
}
