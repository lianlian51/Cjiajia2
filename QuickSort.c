#include <stdio.h>
#include <stdlib.h>

/*int _Quicksort(int *arr,int left,int right)
{
	int index = left;
	int i = left;
	for( i = left + 1; i < right - 1; ++i)	
	{
		if(arr[index] > arr[i])
			index = i;
	}
	return index;
}
*/

void Quicksort(int *arr,int left,int right)
{
	int i = left;
	int tmp = 0;
	int index = left;
	for(i = left; i < right; ++i)
	{
		index = i;
		int j = i + 1;
		for(; j < right; ++j)
		{
			if(arr[index] > arr[j])
				index = j;
		}
		if(index != i)
		{
			tmp = arr[index];
			arr[index] = arr[i];
			arr[i] = tmp;
		}
	}
}

int main()
{
	int arr[] = {1,2,9,8,4,5,6,7};
	int n = sizeof(arr)/sizeof(arr[0]);
	int i = 0;
 	for(i = 0; i < n; ++i)
		printf("%d ",arr[i]);
	printf("\n");
	Quicksort(arr,0,n);

	i = 0;
 	for( i = 0; i < n; ++i)
		printf("%d ",arr[i]);
	printf("\n");
}
