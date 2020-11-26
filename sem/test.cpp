#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <vector>

#define CAPACITY 4

class sem{
  public:
    sem()
      : vv(CAPACITY)
    {
      capacity = CAPACITY;

      sem_init(&lock, 0, 1);
      sem_init(&prod, 0, capacity);
      sem_init(&cons, 0, 0);

      post_read = 0;
      post_write = 0;
    }

    void Push(int data)
    {
      sem_wait(&prod);

      sem_wait(&lock);
      vv[post_write] = data;
      post_write = (post_write + 1) % capacity;
      sem_post(&lock);

      sem_post(&cons);
    }

    void Pop(int* data)
    {
      sem_wait(&cons);

      sem_wait(&lock);
      *data = vv[post_read];
      post_read = (post_read + 1) % capacity;
      sem_post(&lock);

      sem_post(&prod);
    }
    ~sem()
    {
      sem_destroy(&lock);
      sem_destroy(&prod);
      sem_destroy(&cons);
    }


  private:
    std::vector<int> vv;
    int capacity;

    sem_t lock;
    sem_t prod;
    sem_t cons;

    int post_write;
    int post_read;
};


int main()
{
  return 0;
}
