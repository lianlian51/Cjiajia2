#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define PTHREADCOUNT 1

void* myStart(void* arg)
{
  pthread_detach(pthread_self());
  while(1)
  {
    sleep(20);
    printf("i am workspace\n");
    pthread_exit(NULL);
  }
#if 0
  pthread_cancel(pthread_self());
  printf("i am workspace!\n");
#endif
  return NULL;
}


int main()
{
  pthread_t tid[PTHREADCOUNT];
  for(int i = 0; i < PTHREADCOUNT; i++)
  {
    int ret = pthread_create(&tid[i], NULL, myStart, NULL);
    if(ret < 0)
    {
      printf("create error!\n");
      return -1;
    }
  }

  for(int i = 0; i < PTHREADCOUNT; i++)
  {
    // 线程等待
    pthread_join(tid[i], NULL);
    // 线程分离
    pthread_detach(tid[i]);
  }
  return 0;
}
