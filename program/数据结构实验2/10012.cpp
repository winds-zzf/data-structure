#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
typedef int Status;
typedef struct
{
	char bookNum[15];	//���
	char bookName[40];	//����
	float bookPrice;	//�鼮�۸�
}Book;			//����Book���ͽṹ������洢�鼮��Ϣ
typedef struct LNode
{
	Book date;			//���������
	struct LNode* next;	//���ָ����
}LNode, * LinkList;

//�ṹ����������
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
}//���������ʼ��
Status InitList(LinkList& L)
{
	L = new LNode;		//�����½ڵ���Ϊͷ���
	if (!L) exit(LOVERFLOW);

	L->next = NULL;	//�ձ�ָ����Ϊ��
	return OK;
}
//�����������
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //���λ��ָ��
	if (!L->next) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ��
	while (p)
	{
		Output(p->date);
		p = p->next;		//ָ�����
	}
	return OK;
}

//���ս���˳�򴴽�һ�������Զ���ȡ��
void CreateList_D(LinkList &L)
{
	LinkList pre, q, t;		//pre��q�ɶ�ʹ�ã�������������λ�ã�t��ʱ���ָ�룬�Ĵ���ʱ���ɵĽ��
	Book e, m = { "0", "0", 0.0 };

	L = new LNode;		//����һ��������--������
	if (!L) exit(0);
	L->next = NULL;

	Input(e);	//�ȶ���e�����ж�
	while (!BookCmp(e, m))
	{
		pre = L; q = L->next;		//λ�ò���ָ�룬��ÿһ�β����Ƕ���ָ��ͷ������Ԫ���

		while (q && q->date.bookPrice >= e.bookPrice)		//ֻҪqָ��Ľ����ڣ����������ֵ���бȽ�
		{
			pre = q; q = q->next;		//ͬʱ��������ָ�룬�ж���һ��λ��
		}

		t = new LNode; if (!t) exit(OVERFLOW);	t->date = e;	//���벢��ʼ��һ���½��

		pre->next = t; t->next = q;		//�½�������pre��q֮��
		Input(e);			
	}
}
int main()
{
	LinkList L;

	CreateList_D(L);

	ListTraverse(L);
	return 0;
}