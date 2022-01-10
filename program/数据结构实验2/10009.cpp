#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LMAXSIZE 200
typedef int Status;
typedef struct
{
	char bookNum[15];	//���
	char bookName[40];	//����
	float bookPrice;	//�鼮�۸�
}Book;			//����Book���ͽṹ������洢�鼮��Ϣ
typedef struct
{
	Book* base;		//˳����������ַ
	int length;		//˳����
}SqList;		//����һ����ΪSqList��˳���

//�ṹ��������������
void Input(Book& e)
{
	scanf("%s%s%f",
		e.bookNum, 15,
		e.bookName, 40,
		&e.bookPrice
	);
}

//�ṹ�������������
void Output(Book e)
{
	printf("%s %s %.2f\n",
		e.bookNum,
		e.bookName,
		e.bookPrice
	);
}

//˳���ĳ�ʼ��
Status InitList(SqList& L)
{
	L.base = new Book[LMAXSIZE];	//Ϊ˳���������볤ΪLMAXSIZE�Ĵ洢�ռ�
	if (!L.base) exit(OVERFLOW);

	L.length = 0;		//�ձ���Ϊ��
	return OK;
}

//���Ա��ɾ��
Status ListDelete(SqList& L, int i)
{
	int j;
	if (i<1 || i>L.length)  return ERROR;
	for (j = i - 1; j < L.length; j++)
	{
		L.base[j] = L.base[j + 1];
	}
	L.length--;
	return OK;
}


//˳���ı���
Status ListTraverse(SqList L)
{
	if (!L.length) return ERROR;
	for (int i = 0; i < L.length; i++)
	{
		Output(L.base[i]);
	}
	return OK;
}

int main()
{
	Book e;		//book���ͱ����洢�鼮��Ϣ
	SqList L;
	int location;
	InitList(L);
	scanf("%d", &L.length);		//����ĳ���ֱ���޸�L.length

	for (int i = 0; i < L.length; i++)
	{
		Input(e);
		L.base[i] = e;
	}

	scanf("%d", &location);	//������λ��
	if (ListDelete(L, location))	//���������
	{
		ListTraverse(L);
	}
	else
	{
		printf("Sorry��the position to be deleted is invalid!\n");
	}
	return 0;
}