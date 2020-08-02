#include <stdio.h>

int main()
{
	int n = 0;
	printf("请输入要打印*的行数：>");
	scanf("%d",&n);
	int i = n;
	for(i ; i > 0; i--)
	{
		int k = i - 1;
		for(k; k > 0; k--)
			printf(" ");
		int j = 2 *(n - i) + 1;
		for(; j > 0; j--)
			printf("*");
		printf("\n");
	}
	return ;
}
