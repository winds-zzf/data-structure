#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
typedef int Status;

typedef struct LNode
{
	char  data;			//���������
	struct LNode* next;	//���ָ����
}LNode, * LinkList;

//���������ʼ��
Status InitList(LinkList& L)
{
	L = new LNode;
	if (!L) exit(LOVERFLOW);
	L->next = NULL;
	return OK;
}

//�����������
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //���λ��ָ��
	if (!L->next) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ��
	while (p->next)
	{
		printf("%c ", p->data);
		p = p->next;		//ָ�����
	}
	printf("%c\n", p->data);
	return OK;
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

//������������
Status DestoryList(LinkList& L)
{
	LinkList p;			//��ʱ���
	while (L)
	{
		p = L; L = L->next; delete p;		//�Ĵ棬 �ƶ��� ɾ��
	}
	return  OK;
}

//��巨������������
Status CreateList_H(LinkList& L, int n)
{
	LinkList pt;		//β���ָ�룬ʼ��ָ��β��㣻��ʱָ��

	L = new LNode;
	if (!L) exit(LOVERFLOW);
	L->next = NULL;

	for (int i = 0; i < n; i++)
	{
		pt = new LNode; if (!pt) exit(LOVERFLOW);		//�����½�㲢��ʼ��������;
		scanf_s(" %c", &pt->data, 1);

		pt->next = L->next;
		L->next = pt;
	}

	return OK;
}

//�������ܣ��ϲ�����ͬ��׺�ĵ���
char MergeSameSuffix(LinkList LA, LinkList LB)
{
	LinkList pa,pre, pb;
	pre = LA; pa = LA->next;	//��ʼ��ָ��
	pb = LB->next;

	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			pre = pa; pa = pa->next;	//pa��Ҫ��¼��ֱ��ǰ������Ϣ�����Ҫ�и�pre
			pb = pb->next;		
		}
		else	//����Ĳ�����ǽ���������������Ϊ�յĻ����ϵģ���˿���������Ȼ�˳�
		{
			break;
		}
	}
	return pre->data;
}

int main()
{
	int n_A, n_B;
	LinkList A, B;

	scanf_s("%d%d", &n_A, &n_B);		//����A�� B�ĳ���
	do
	{
		InitList(A);
		InitList(B);

		CreateList_H(A, n_A);			//��ʼ��A��B����
		CreateList_H(B, n_B);

		printf("%c\n", MergeSameSuffix(A, B));
		DestoryList(A);
		DestoryList(B);

		scanf_s("%d%d", &n_A, &n_B);		//����A�� B�ĳ���
	} while (n_A!=0 || n_B!=0);

	return 0;
}