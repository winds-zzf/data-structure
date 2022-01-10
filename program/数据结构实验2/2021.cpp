#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define MAXSIZE 100

//输入一个整形数组
void  CreateArray(int* &p , int m, int n)
{
	p = new int[m * n];		//申请行列为m, n的一维数组
	if (!p) exit(OVERFLOW);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", p + i * n + j);
		}
	}
}

//函数功能：数组数据查重
int Rechecking(int *p, int len)
{
	int j;
	for (int i = 0; i < len-1; i++)
	{
		for (j = i+1; j < len; j++)
		{
			if (p[i] == p[j]) return 0;
		}
	}
	return 1;		//一直检查到最后而没有中途返回，说明无重复
}

int main()
{
	int* A = NULL;
	int m, n;

	scanf("%d%d", &m, &n);
	while (m!=0 || n!=0)
	{
		CreateArray(A, m, n);
		if (Rechecking(A, m * n)) printf("NO\n");
		else	printf("YES\n");
		scanf("%d%d", &m, &n);
	}

	return 0;
}