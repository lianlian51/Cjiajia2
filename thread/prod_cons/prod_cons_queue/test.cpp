#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <iostream>

// 生产者与消费者模型
//  1.线程安全的队列
//     std::queue 
//     同步：pthread_cond_t
//     互斥：pthread_mutex_t
//  2.两种角色的线程
//     生产者线程-->生产者入口函数
//     消费者线程-->消费者入口函数

#define THREADCOUNT 2 

class BlockQueue
{
  public:
    BlockQueue()
    {
      capacity_ = 10;
      pthread_mutex_init(&lock_, NULL);
      pthread_cond_init(&prod, NULL);
      pthread_cond_init(&cons, NULL);
    }

    ~BlockQueue()
    {
      pthread_mutex_destroy(&lock_);
      pthread_cond_destroy(&prod);
      pthread_cond_destroy(&cons);
    }

    // 写多线程代码的时候
    //   1.考虑业务核心逻辑
    //   2.考虑核心逻辑当中是否访问临界资源，如果有则保证互斥
    //   3.需不需要保证各个线程的同步
    
    // 生产者线程
    void Push(int data)
    {
      pthread_mutex_lock(&lock_);

      while(que_.size() >= capacity_)
      {
        pthread_cond_wait(&prod, &lock_);
      }
      que_.push(data);

      pthread_mutex_unlock(&lock_);

      pthread_cond_signal(&cons);
    }

    // 消费者线程
    void Pop(int *data)
    {
      pthread_mutex_lock(&lock_);

      while(que_.size() <= 0)
      {
        pthread_cond_wait(&cons, &lock_);
      }

      *data = que_.front();
      que_.pop();

      pthread_mutex_unlock(&lock_);

      pthread_cond_signal(&prod);
    }
  private:
    // STL 提供的queue是不安全的
    std::queue<int> que_;

    size_t capacity_;

    pthread_mutex_t lock_;
    pthread_cond_t cons;
    pthread_cond_t prod;
};

void* ConsStart(void* arg)
{
  BlockQueue* bq = (BlockQueue*)arg;
  while(1)
  {
    // 从线程安全队列中获取数据消费
    int data;
    bq->Pop(&data);
    printf("i am thread : %p, data: %d\n", pthread_self(), data);
  }
  return NULL;
}

void* ProdStart(void* arg)
{
  BlockQueue* bq = (BlockQueue*)arg;
  int data = 0;
  while(1)
  {
    // 从线程队列当中插入数据
    bq->Push(data);
    printf("i am thread : %p, data: %d\n", pthread_self(), data);
    data++;
  }
  return NULL;
}

int main()
{
  pthread_t cons[THREADCOUNT], prod[THREADCOUNT];

  BlockQueue* bq = new BlockQueue();

  for(int i = 0; i < THREADCOUNT; i++)
  {
    int ret = pthread_create(&cons[i], NULL, ConsStart, (void*)bq);
    if(ret < 0)
    {
      perror("cons create error!\n");
      return -1;
    }
    ret = pthread_create(&prod[i], NULL, ProdStart, (void*)bq);
    if(ret < 0)
    {
      perror("prod create error!\n");
      return -1;
    }
  }

  for(int i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(prod[i], NULL);
    pthread_join(cons[i], NULL);
  }
  return 0;
}
