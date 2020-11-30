#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <vector>

#define CAPACITY 4
#define THREADCOUNT 2

class sem
{
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

void* ConsStart(void* arg)
{
  sem* sq = (sem*)arg;
  while(1)
  {
    int data;
    sq->Pop(&data);
    printf("i am thread %p, data : %d\n", pthread_self(), data);
  }
  return NULL;
}

void* ProdStart(void* arg)
{
  sem* sq = (sem*)arg;
  int data = 0;
  while(1)
  {
    sq->Push(data);
    printf("i am thread %p, data : %d\n", pthread_self(), data);
    data++;
  }
  return NULL;
}

int main()
{
  pthread_t cons[THREADCOUNT], prod[THREADCOUNT];

  sem* sq = new sem();

  for(int i = 0; i < THREADCOUNT; i++)
  {
    int ret = pthread_create(&cons[i], NULL, ConsStart, (void*)sq);
    if(ret < 0)
    {
      perror("cons error!\n");
      return -1;
    }
    ret = pthread_create(&prod[i], NULL, ProdStart, (void*)sq);
    if(ret < 0)
    {
      perror("cons error!\n");
      return -1;
    }
  }

  for(int i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(cons[i], NULL);
    pthread_join(prod[i], NULL);
  }
  return 0;
}
