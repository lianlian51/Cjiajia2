#include <cstdio>

class Singleton2{
  private:
    static int* data;
  public:
    static int* GetInstance(){
      if(data == NULL)
      {
        data = new int;
      }
      return data;
    }
};

int *Singleton2::data = NULL;

int main()
{
  *Singleton2::GetInstance() = 20;
  printf("a:%d\n",*Singleton2::GetInstance());
}
