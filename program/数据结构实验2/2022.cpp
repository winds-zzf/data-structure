#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100


int main()
{
	int n, j;
	int src[MAXSIZE], dst[MAXSIZE] = {0};

	scanf("%d", &n);
	while (n)
	{
		j = 0;		//��ÿһ������ǰ��ʼ��j
		for (int i = 0; i < n; i++)		//��������
		{
			scanf("%d", src+i);
		}

		for (int i = 0; i < n; i++)
		{
			if (src[i] > 0) 
			{
				dst[j] = src[i];
				j++;		//j��������
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (src[i] < 0)
			{
				dst[j] = src[i];
				j++;		//j��������
			}
		}

		for (j = 0; j < n-1; j++)
		{
			printf("%d ", dst[j]);
		}
		printf("%d\n", dst[j]);

		scanf("%d", &n);
	}

	return 0;
}