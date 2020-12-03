#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>

typedef void(*Handler) (int);

class QueueData
{
  public:
    QueueData(int data, Handler handler)
    {
      data_ = data;
      handler_ = handler;
    }

    ~QueueData()
    {

    }

#if 0
    int Getdata()
    {
      return data_;
    }
    Handler GetHandler()
    {
      return handler_;
    }
#endif

    void Run()
    {
      handler_(data_);
    }
  private:
    int data_;
    Handler handler_;
};

class Threadpool
{
  public:
    Threadpool(int capacity, int thread_count)
    {
      capacity_ = capacity;
      thread_count_ = thread_count;
      
      pthread_mutex_init(&lock_, NULL);
      pthread_cond_init(&cons_, NULL);

      flag = 0;
    }

    ~Threadpool()
    {
      pthread_mutex_destroy(&lock_);
      pthread_cond_destroy(&cons_);
    }

    // 线程池初始化
    int Oninit()
    {
      // 线程创建
      pthread_t tid;
      for(int i = 0; i < thread_count_; i++)
      {
        int ret = pthread_create(&tid, NULL, Startpool, (void*)this);
        if(ret < 0)
        {
          perror("create error!\n");
          return -1;
        }
      }
      return 0;
    }

   int Push(QueueData* qd)
   {
     pthread_mutex_lock(&lock_);
     if(flag)
     {
       pthread_mutex_unlock(&lock_);
       return -1;
     }

     que_.push(qd);

     pthread_mutex_unlock(&lock_);

     pthread_cond_signal(&cons_);
     return 0;
   }

   void ThreadExit()
   {
     pthread_mutex_lock(&lock_);
     flag = 1;
     pthread_mutex_unlock(&lock_);

     pthread_cond_broadcast(&cons_);
   }

  private:
   void Pop(QueueData** data)
   {
     *data = que_.front();
     que_.pop();
   }

   static void* Startpool(void *arg)
   {
     pthread_detach(pthread_self());
     Threadpool *tp = (Threadpool*)arg;
     while(1)
     {
       pthread_mutex_lock(&tp->lock_);
       while(tp->que_.empty())
       {
         if(tp->flag)
         {
           tp->thread_count_--;
           pthread_mutex_unlock(&tp->lock_);
           pthread_exit(NULL);
         }
         pthread_cond_wait(&tp->cons_, &tp->lock_);
       }
       QueueData* qd;
       tp->Pop(&qd);
       pthread_mutex_unlock(&tp->lock_);
       qd->Run();
       delete qd;
     }
   }

  private:
    std::queue<QueueData*> que_;
    size_t capacity_;

    pthread_mutex_t lock_;
    // pthread_cond_t prod_;
    pthread_cond_t cons_;

    // 线程的数量
    int thread_count_;

    int flag;
};

void Dealdata(int data)
{
  printf("data: %d\n", data);
}

int main()
{
  Threadpool* tp = new Threadpool(4, 2);
  if(!tp)
  {
    printf("create threadpool error!\n");
    return -1;
  }

  int ret = tp->Oninit();
  if(ret < 0)
  {
    printf("Oninit error!\n");
    return -1;
  }

  for(int i = 0; i < 100; i++)
  {
    QueueData* qd = new QueueData(i, Dealdata);
    if(!qd)
    {
      continue;
    }
    tp->Push(qd);
  }

  sleep(5);
  tp->ThreadExit();
  delete tp;
  return 0;
}
