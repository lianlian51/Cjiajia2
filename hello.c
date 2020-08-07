#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
   printf("hello linux\n");
   pid_t pid = fork();
   printf("this is progress\n");
   return;
}
