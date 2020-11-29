#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADCOUNT 4

int g_tikets = 100;
pthread_mutex_t lock;

void* myStart(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);
    if(g_tikets > 0)
    {
      printf("i am thread %p, g_tikets = %d\n", pthread_self(), g_tikets);
      g_tikets--;
    }
    else {
      pthread_mutex_unlock(&lock);
      break;
    }
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}


int main()
{
  pthread_mutex_init(&lock, NULL);
  pthread_t tid[THREADCOUNT];
  for(int i = 0; i < THREADCOUNT; i++)
  {
    int ret = pthread_create(&tid[i], NULL, myStart, NULL);
    if(ret < 0)
    {
      perror("create error!\n");
      return -1;
    }
  }

  for(int i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(tid[i], NULL);
  }
  pthread_mutex_destroy(&lock);
  return 0;
}
