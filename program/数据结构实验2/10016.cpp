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
Status CreateList_R(LinkList& L, int n)
{
	LinkList p, t;		//βָ��p, ��ʱ���ָ��r���Ĵ������ɽ���ַ
	Book e;

	L = new LNode; if (!L) exit(LOVERFLOW);		//����һ���ձ����ж��Ƿ�ɹ�
	L->next = NULL;

	p = L;		//ͷ�巨��ʼʱָ��ͷָ��
	for (int i = 0; i < n; i++)
	{
		t = new LNode;			//����һ���½��,����������
		if (!t) exit(LOVERFLOW);
		Input(e);	t->date = e;

		p->next = t; t->next = NULL; p = t;		//β�巨�и�βָ�룬һֱ��ֻ��β���
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

//��Ѱ��鼮
Status SearchList(LinkList L, Book e)
{
	LinkList p;		//���λ��ָ��
	int counter = 0;	//������
	if (!L->next) return ERROR;

	p = L->next;
	while (p)
	{
		if (!strcmp(p->date.bookName, e.bookName)) counter++;
		p = p->next;
	}

	if (counter == 0) printf("Sorry��there is no your favourite!\n");
	else
	{
		printf("%d\n", counter);
		p = L->next;		//p����ָ���ʼλ��
		while (p)
		{
			if (!strcmp(p->date.bookName, e.bookName)) Output(p->date); 
			p = p->next;
		}
	}

	return OK;
}


int main()
{
	LinkList L;
	int num, times;
	Book e;

	scanf("%d", &num);
	CreateList_R(L, num);
	scanf("%d", &times);
	for (int i = 0; i < times; i++)
	{
		scanf("%s", e.bookName, 40);
		SearchList(L, e);
	}

	return 0;
}