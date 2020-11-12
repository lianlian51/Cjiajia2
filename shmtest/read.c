#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 0x89898989

int main()
{
  int shmid = shmget(KEY, 1024, IPC_CREAT | 0664);
  if(shmid < 0)
  {
    perror("shmid error\n");
    return -1;
  }

  void* lp = shmat(shmid, NULL, 0);
  printf("%s\n", (char*)lp);
  printf("%s\n", (char*)lp);
  printf("%s\n", (char*)lp);
  printf("%s\n", (char*)lp);
  printf("%s\n", (char*)lp);
  printf("%s\n", (char*)lp);
  
  struct shmid_ds buf;
  shmctl(shmid, IPC_STAT, &buf);

  printf("shm size : %d\n", buf.shm_segsz);

  //shmdt(lp);
  while(1)
  {
    sleep(1);
  }
  return 0;
}
