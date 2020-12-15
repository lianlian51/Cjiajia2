#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
using namespace std;

class NQueue{
  private:
    std::vector<int> place; // 放置皇后
    std::vector<int> flag;  // 标记已经放过的列
    std::vector<int> d1; // 主对角线的差值相等，有负数的情况，所以要加7
    std::vector<int> d2; // 次对角线的和相等
    int count_ = 0; // 计算成功摆放的次数
    int n;


  public:
    NQueue(int n_)
      : n(n_)
    {
      place.resize(n, 0);
      flag.resize(n, 0);
      int  line = 2 * n - 1;
      d1.resize(line, 0);
      d2.resize(line, 0);
    }

    int GetCount()
    {
      return count_;
    }

    void show()
    {
      cout << "NO." << ++count_ << endl;
      for(int i = 0; i < n; i++)
      {
        for(int j = 0; j < n; j++)
        {
          if(place[i] == j)
            std::cout << "1";
          else 
            std::cout << "0";
        }
        std::cout << endl;
      }
    }

    void search(int k) // k:代表行
    {
      for(int i = 0; i < n; i++) // 代表列
      {
        if(flag[i] == 0 && d1[k - i + n - 1] == 0 && d2[k + i] == 0)
        {
          place[k] = i;
          flag[i] = 1;
          d1[k - i + n - 1] = 1;
          d2[k + i] = 1;
          if(k == n - 1)
          {
            //count_++;
            show();
          }
          else
          {
            search(k + 1);
          }
          flag[i] = 0;
          d1[k - i + n - 1] = 0;
          d2[k + i] = 0;
        }
      }
    }
};

int main()
{
  int n;
  std::cout << "请输入N个皇后：";
  std::cin >> n;
  NQueue q(n);
  q.search(0);
  printf("一共有%d中方法\n", q.GetCount());
  return 0;
}
