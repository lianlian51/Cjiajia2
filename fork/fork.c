#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid > 0)
	{
		printf("this is parents:%d\n",getpid());
	}else if(pid == 0)
	{
		printf("this is child:%d\n",getpid());
	}
	else
		printf("perror\n");

	sleep(100);
	printf("this is progress\n");

}
