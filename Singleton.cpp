#include <cstdio>

class Singleton{
  private:
    static int data;
  public:
    static int* GetInstance(){
      return &data;
    }
};

int Singleton::data = 10;

int main()
{
  Singleton a,b;
  printf("a : %d\n", *a.GetInstance());
  printf("b : %d\n", *b.GetInstance());

  *b.GetInstance() = 20;
  printf("a : %d\n", *a.GetInstance());
  printf("b : %d\n", *b.GetInstance());

}
