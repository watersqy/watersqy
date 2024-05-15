#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int a[100] = { 0 };
	srand((unsigned)time(0));
	int i, j, tmp;
	for (i = 0; i < 100; i++)
	{
		a[i] = rand() % 1000 + 1;
	}
	printf("排序前的数组：\n");
	for (i = 0; i < 100; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	for (i = 1; i < 100; i++)
	{
		tmp = a[i];
		j = i;
		while (j > 0 && a[j - 1 ]> tmp)
		{
			a[j] = a[j - 1];
			j--;
		}
		a[j] = tmp;
	}
	printf("排序后的数组：\n");
	for (i = 0; i < 100; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}