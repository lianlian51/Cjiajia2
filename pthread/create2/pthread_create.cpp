#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct Data{
  int data_;
};

void* myStart(void* arg)
{
  Data* d = (Data*)arg;
  while(1)
  {
    printf(" workspace :%p, i = %d\n", pthread_self(), d->data_);
    sleep(1);
  }

  delete d;
  d = NULL;

  return NULL;
}



int main()
{
  pthread_t tid;
  for(int i = 0; i < 4; i++)
  {
    Data* d = new Data();
    d->data_= i;
    int ret = pthread_create(&tid, NULL, myStart, (void*)d);
    if(ret < 0)
    {
      perror("pthread error!\n");
      return -1;
    }
  }

  while(1)
  {
    printf("i am main pthread!\n");
    sleep(1);
  }
  return 0;
}
