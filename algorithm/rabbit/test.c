// 这里解决的是：有一只兔子，从出生后第3个月起每个月都生一只兔子，
// 小兔子长到第三个月后每个月又生一只兔子，假如兔子都不死，问每个月的兔子总数为多少？
//
// 这里需要理解的是：兔子刚到三个月就可以进行生育

#include <stdio.h>
#include <unistd.h>

int getRabbit(int n)
{
  int n1 = 1, n2 = 0, n3 = 0;
  while(--n)
  {
    // n3:两个月和三个月兔子的总和
    n3 += n2;
    // n2:一个月到两个月的兔子数
    n2 = n1;
    // n1:第三个月出生的兔子数
    n1 = n3;
  }
  return n1 + n2 + n3;
}

int main()
{
  int n;
  while(scanf("%d", &n))
  {
    int num = getRabbit(n);
    printf("%d\n", num);
  }
  return 0;
}
