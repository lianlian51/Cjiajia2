#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADCOUNT 1

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* Threadlock1(void* arg)
{
  (void)arg;
  pthread_mutex_lock(&lock1);

  sleep(2);

  pthread_mutex_lock(&lock2);
  pthread_mutex_unlock(&lock2);
  pthread_mutex_unlock(&lock1);

  return NULL;
}


void* Threadlock2(void* arg)
{
  (void)arg;
  pthread_mutex_lock(&lock2);

  sleep(2);

  pthread_mutex_lock(&lock1);
  pthread_mutex_unlock(&lock1);
  pthread_mutex_unlock(&lock2);

  return NULL;
}

int main()
{
  pthread_mutex_init(&lock1, NULL);
  pthread_mutex_init(&lock2, NULL);


  pthread_t tid1[THREADCOUNT], tid2[THREADCOUNT];

  for(int i = 0; i < THREADCOUNT; i++)
  {
    int ret = pthread_create(&tid1[i], NULL, Threadlock1, NULL);
    if(ret < 0)
    {
      perror("thread1 error!\n");
      return -1;
    }

    ret = pthread_create(&tid1[i], NULL, Threadlock2, NULL);
    if(ret < 0)
    {
      perror("thread2 error!\n");
      return -1;
    }
  }
  sleep(3);


  for(int i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(tid1[i], NULL);
    pthread_join(tid2[i], NULL);
  }
  pthread_mutex_destroy(&lock1);
  pthread_mutex_destroy(&lock2);

  return 0;
}
