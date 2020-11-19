#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* Tstart(void* arg)
{
  while(1)
  {
    printf("i am work_pthread!\n");
    sleep(1);
  }
  return NULL;
}


int main()
{
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, Tstart, NULL);
  if(ret < 0)
  {
    perror("create error!\n");
    return -1;
  }

  while(1)
  {
    printf("i am main_pthread\n");
    sleep(1);
  }
  return 0;
}
