#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define MAXSIZE 100

//����һ����������
void  CreateArray(int* &p , int m, int n)
{
	p = new int[m * n];		//��������Ϊm, n��һά����
	if (!p) exit(OVERFLOW);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", p + i * n + j);
		}
	}
}

//�������ܣ��������ݲ���
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
	return 1;		//һֱ��鵽����û����;���أ�˵�����ظ�
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