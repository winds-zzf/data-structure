#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#define LMAXSIZE 100
#include<stdio.h>
#include<stdlib.h>

typedef int Status;
typedef struct LNode
{
	int date;			//���������
	struct LNode* next;	//���ָ����
}LNode, * LinkList;

//���������ʼ��
Status InitList(LinkList& L)
{
	L = new LNode;		//�����½ڵ���Ϊͷ���
	if (!L) exit(LOVERFLOW);

	L->next = NULL;	//�ձ�ָ����Ϊ��
	return OK;
}

//�����������
Status ClearList(LinkList L)
{
	LinkList p;
	while (L->next)		//����ͷ���
	{
		p = L->next; L->next = p->next; delete p;		//�Ĵ棬 �ƶ��� ɾ����
	}
	return OK;
}

//�����������
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //���λ��ָ��
	if (!L->next) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ��
	while (p)
	{
		printf("%d ", p->date);
		p = p->next;		//ָ�����
	}
	return OK;
}

//���������β�巨����
Status CreateList_R(LinkList& L, int n)
{
	LinkList p, t;		//βָ��p, ��ʱ���ָ��r���Ĵ������ɽ���ַ
	int e;

	L = new LNode; if (!L) exit(LOVERFLOW);		//����һ���ձ����ж��Ƿ�ɹ�
	L->next = NULL;

	p = L;  //ָ����Ԫ���λ��
	for (int i = 0; i < n; i++)
	{
		t = new LNode; if (!t) exit(LOVERFLOW);		//����һ���½��

		scanf("%d", &e);  t->date = e;						//��ȡ���ݣ��������½����

		p->next = t; t->next = NULL; p = t;				//ÿһ�ζ�Ҫ�ڲ������β���ָ����Ϊ�գ���Ϊ��֪���Ǵ�Ҫ�������½ڽ��ʧ���������û�н�����־��
	}
	return OK;
}

//���õݹ�����ƽ��ֵ
int  Sum(LinkList L)
{
	if (L) return L->date + Sum(L->next);
	else return 0;
}

//����������
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

int main()
{
	int m;
	LinkList A;
	InitList(A);

	scanf("%d", &m);
	while (m)
	{
		CreateList_R(A, m);
		printf("%.2f\n", Sum(A->next) / (double)ListLength(A));
		ClearList(A);
		scanf("%d", &m);
	}

	return 0;
}