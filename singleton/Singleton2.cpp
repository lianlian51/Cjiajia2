#include <cstdio>
#include <mutex>

class Singleton2{
  private:
    volatile static int* data;
    static std::mutex lock;
    Sintleton2();
  public:
    volatile static int* GetInstance(){
      if(data == NULL)
      {
        lock.lock();
        if(data == NULL)
          data = new int;
        lock.unlock();
      }
      return data;
    }
};

std::mutex Singleton2::lock;
volatile static int *Singleton2::data = NULL;

int main()
{
  *Singleton2::GetInstance() = 20;
  printf("a:%d\n",*Singleton2::GetInstance());
}
