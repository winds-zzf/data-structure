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

//�Ƚ������ṹ���Ƿ���ͬ
Status BookCmp(Book elem_1, Book elem_2)
{
	if (!strcmp(elem_1.bookNum, elem_2.bookNum))
	{
		if (!strcmp(elem_1.bookName, elem_2.bookName))
		{
			if (fabs((double)elem_1.bookPrice - (double)elem_2.bookPrice) < 0.0001)
				return OK;
		}
	}
	return ERROR;
}
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
//˳���Ĳ���:������ָ��λ�ã���ţ����±�
Status InsertElem(SqList& L, int i, Book e)
{
	if (i<1 || i>L.length + 1) return ERROR;
	if (L.length == LMAXSIZE) return ERROR;

	for (int j = L.length - 1; j >= i - 1; j--)
	{
		L.base[j + 1] = L.base[j];
	}
	L.base[i - 1] = e;		//��i��λ�ò��룬�±�Ϊi-1
	L.length++;
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
	Book e, m = {"0", "0", 0.0};		//book���ͱ����洢�鼮��Ϣ
	SqList L;
	InitList(L);

	Input(e);
	for (int i = 1; !BookCmp(m, e); i++)
	{
		InsertElem(L, i, e);
		Input(e);
	}
	printf("%d\n", L.length);			//�������
	ListTraverse(L);
	return 0;
}