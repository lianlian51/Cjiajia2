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
    perror("shmget error\n");
    return -1;
  }
  // 0 :可读可写
  // 附加
  void* lp = shmat(shmid, NULL, 0);
  strcpy((char*)lp, "hello stars\n");

  // 分离
  shmdt(lp);

  // 删除共享内存
  shmctl(shmid, IPC_RMID, NULL);

  while(1)
  {
    sleep(1);
  }
  return 0;
}
