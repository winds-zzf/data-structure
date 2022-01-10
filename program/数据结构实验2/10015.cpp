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

//ǰ�巨����������
Status CreateList_H(LinkList& L, int n)
{
	LinkList t;		//βָ��p, ��ʱ���ָ��r���Ĵ������ɽ���ַ
	Book e;

	L = new LNode; if (!L) exit(LOVERFLOW);		//����һ���ձ����ж��Ƿ�ɹ�
	L->next = NULL;

	for (int i = 0; i < n; i++)
	{
		t = new LNode;			//����һ���½��,����������
		if (!t) exit(LOVERFLOW);
		Input(e);	t->date = e;

		t->next = L->next; L->next = t;
	}
	return OK;
}

//ͼ����Ϣ����洢
Status CreateList_D(LinkList& L, int n)
{
	LinkList pre, q, t;  //��λָ�룬 ��ʱָ��
	Book e;		//�洢�������

	L = new LNode; if (!L) exit(OVERFLOW); L->next = NULL;		//����һ���ձ�
	for (int i = 0; i < n; i++)
	{
		pre = L; q = L->next;		//��ÿһ���������ǰ����ʼ��λ��ָ��

		Input(e);
		while (q && q->date.bookPrice >= e.bookPrice)
		{
			pre = q; q = q->next;		//λ��ָ�����
		}

		t = new LNode; if (!t) exit(OVERFLOW); t->date = e;	//�����½�㲢��ʼ����

		pre->next = t; t->next = q;		//�����½��
	}
	return OK;
}

//��Ѱ����鼮
Status SearchList(LinkList L)
{
	LinkList p;
	float temp;
	int counter;
	if (!L->next) return ERROR;
	temp = L->next->date.bookPrice;		//�����������������������ǰ����
	counter = 1;
	p = L->next->next;	//����Ԫ����ֱ�Ӻ�̿�ʼ
	while (p->date.bookPrice == temp)
	{
		p = p->next; counter++;
	}

	printf("%d\n", counter);
	p = L->next;		//����ָ����Ԫ���
	for (int i = 1; i <= counter; i++)
	{
		Output(p->date);  p = p->next;
	}
	return OK;
}


int main()
{
	LinkList L;
	int num;

	scanf("%d", &num);
	CreateList_D(L, num);

	SearchList(L);

	return 0;
}