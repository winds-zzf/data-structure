#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OVERFLOW -1

typedef struct
{
	int* base;		//�������ַ
	int length;		//����˳�����
}SqList;

int InitList(SqList &L)
{
	L.base = new int[MAXSIZE];
	if (!L.base) exit(OVERFLOW);
	L.length = 0;
	return 1;
}



//�������ܣ�������������
void CreateList(SqList &L, int n)
{
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", L.base+i);
	}
	L.length = n;
}

//�������ܣ������������
void TraverseList(SqList L, int loc)
{
	int i;
	for (i = 0; i < L.length-1; i++)
	{
		loc = loc % L.length;
		printf("%d ", L.base[loc++]);
	}
	if (i == L.length-1)
	{
		loc = loc % L.length;
		printf("%d\n", L.base[loc++]);

	}
}


int main()
{
	int n, loc;
	SqList L;
	InitList(L);

	scanf_s("%d", &n);
	do
	{
		CreateList(L, n);
		scanf_s("%d", &loc);		//��ȡƫ����loc
		TraverseList(L, loc);		//���ƶ�Ԫ��λ�ã���ȡѭ�������������ʵ��ĵ�ַת��
		
		scanf_s("%d", &n);
	} while (n != 0);

	return 0;
}