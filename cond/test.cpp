#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADCOUNT 2

int g_bowl = 0;
pthread_mutex_t g_mut;
pthread_cond_t g_cond;

void* MakeStart(void *arg)
{
 while(1)
  {
    pthread_mutex_lock(&g_mut);

    while(g_bowl > 0)
    {
      pthread_cond_wait(&g_cond, &g_mut);
    }

    g_bowl++;
    printf("i am make %p, g_bowl: %d\n", pthread_self(), g_bowl);

    pthread_mutex_unlock(&g_mut);

    pthread_cond_signal(&g_cond);
  }
  return NULL;
}

void* EatStart(void *arg)
{
  while(1)
  {
    // eat
    pthread_mutex_lock(&g_mut);

    while(g_bowl <= 0)
    {
      pthread_cond_wait(&g_cond, &g_mut);
    }

    g_bowl--;
    printf("i am make %p, g_bowl: %d\n", pthread_self(), g_bowl);

    pthread_mutex_unlock(&g_mut);

    // 通知等待队列做面的人
    pthread_cond_signal(&g_cond);
  }
  return NULL;
}

int main()
{
  pthread_mutex_init(&g_mut, NULL);
  pthread_cond_init(&g_cond, NULL);

  pthread_t prod[THREADCOUNT], cons[THREADCOUNT];
  for(int i = 0; i < THREADCOUNT; i++)
  {
    int ret = pthread_create(&prod[i], NULL, MakeStart, NULL);
    if(ret < 0)
    {
      perror("prod create error!\n");
      return -1;
    }


    ret = pthread_create(&prod[i], NULL, EatStart, NULL);
    if(ret < 0)
    {
      perror("cons create error!\n");
      return -1;
    }
  }

  for(int i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(prod[i], NULL);
    pthread_join(cons[i], NULL);
  }

  pthread_mutex_destroy(&g_mut);
  pthread_cond_destroy(&g_cond);
  return 0;
}
