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

//�����ȼ���
int ListLength(LinkList L)
{
	LinkList p;		//���λ��ָ��
	int j;
	p = L->next; j = 0; //��ʼ���λ��ָ�룬������ֵΪ�㣬��Ϊ�����ǿձ�
	while (p)
	{
		j++;  p = p->next;		//���жϽ���Ƿ���ڣ�Ȼ��������ڼ�һ���������һλ
	}
	return  j;
}

//��������ȡֵ����������ҵ�ָ��Ԫ�أ�
Status GetElem(LinkList L, int i, Book& e)
{
	LinkList p;		//���λ��ָ��p;
	int j;
	p = L->next; j = 1;
	while (p && j < i)
	{
		p = p->next; j++;
	}
	if (!p || j > i) return ERROR;
	e = p->date;		//���ز��ҵ���ֵ
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

//������Ϣȥ��
Status RemainOnly(LinkList L)
{
	LinkList pre, q, t;	//��ʱλ��ָ��
	
	t = L->next;
	while (t&&t->next)				//��tָ�����ڶ�����㣬ǡ�ɰ����һ����ɾ���ˣ���ôt->next��ΪNULL��������while�����ж���t->next�����NULLָ�������
	{
		pre = t;  q = t->next;	//ֻ�б�֤��t->next��Ϊ�գ����ܱ�֤q��ʼֵ��Ϊ��

		while (q)
		{
			if (BookCmp(t->date, q->date))
			{
				pre->next = q->next; delete q; q = pre->next;
			}
			else
			{
				pre = q;		//��¼���ڱȽϵĽ���ǰһ���ڵ�
				q = q->next;
			}
		}
		t = t->next;
	}
	return OK;
}

int main()
{
	LinkList L;
	int num;

	scanf("%d", &num);
	CreateList_R(L, num);

	RemainOnly(L);
	printf("%d\n", ListLength(L));
	ListTraverse(L);
	return 0;
}