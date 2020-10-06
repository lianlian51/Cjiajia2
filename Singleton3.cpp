#include <cstdio>
#include <mutex>

class Singleton3{
  private:
    volatile static int* data;
    static std::mutex lock;
    Singleton3();
  public :
    volatile static int* GetInstance(){
      if(data == NULL)
      {
        lock.lock();
        if(data == NULL)
        {
          data = new int;
        }
        lock.unlock();
        return data;
      }
    }
};

std::mutex Singleton3::lock;
volatile int *Singleton3::data = NULL;

int main()
{
  *Singleton3::GetInstance() = 20;
  printf("a:%d\n",Singleton3::GetInstance());
}
