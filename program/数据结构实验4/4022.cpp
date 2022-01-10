#pragma once
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;

typedef struct LNode
{
	int date;			//���������
	struct LNode* next;	//���ָ����
}LNode, * LinkList;

//���������β�巨����
Status CreateList_R(LinkList& L, int n)
{
	LinkList p, t;		//βָ��p, ��ʱ���ָ��r���Ĵ������ɽ���ַ

	L = new LNode; if (!L) exit(LOVERFLOW);		//����һ���ձ����ж��Ƿ�ɹ�
	L->next = NULL;

	p = L;  //ָ��ͷ���λ��
	for (int i = 0; i < n; i++)
	{
		t = new LNode; if (!t) exit(LOVERFLOW);		//����һ���½��

		scanf_s("%d", &t->date); 					//��ȡ���ݣ��������½����

		p->next = t; t->next = NULL; p = t;				//ÿһ�ζ�Ҫ�ڲ������β���ָ����Ϊ�գ���Ϊ��֪���Ǵ�Ҫ�������½ڽ��ʧ���������û�н�����־��
	}
	return OK;
}

//����ͷ���ĵ�������������
void SortList(LinkList L)
{
	LNode* p, * q, * t;
	int temp;
	if (L && L->next)		//�����������Ͻ�㣬���б�Ҫ����
	{
		p = L;
		while (p->next)		//�����ѡ������
		{
			q = p->next;	//q��ʼΪp��ֱ�Ӻ��
			t = p;
			while (q)
			{
				if (q->date < t->date)  t = q;			//��������޸�
				q = q->next;
			}

			if (t != p)
			{
				temp = t->date;
				t->date = p->date;
				p->date = temp;
			}					//����t��p

			p = p->next;		//���pָ�����
		}
	}
}

//�����������
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //���λ��ָ��
	if (!L->next) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ��
	while (p->next)
	{
		printf("%d ", p->date);
		p = p->next;		//ָ�����
	}
	printf("%d\n", p->date);
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

//������������
Status CreateList_U(LinkList& L, int n)
{
	LinkList pre, q, t;  //��λָ�룬 ��ʱָ��
	int e;		//�洢�������

	L = new LNode; if (!L) exit(LOVERFLOW); L->next = NULL;		//����һ���ձ�
	for (int i = 0; i < n; i++)
	{
		pre = L; q = L->next;		//��ÿһ���������ǰ����ʼ��λ��ָ��

		scanf_s("%d", &e);
		while (q && q->date <= e)
		{
			pre = q; q = q->next;		//λ��ָ�����
		}

		t = new LNode; if (!t) exit(LOVERFLOW); t->date = e;	//�����½�㲢��ʼ����

		pre->next = t; t->next = q;		//�����½��
	}
	return OK;
}

int main()
{
	LinkList L;
	int n;

	scanf_s("%d", &n);
	while (n)
	{
		CreateList_U(L, n);

		//		SortList(L);
		ListTraverse(L);

		ClearList(L);
		scanf_s("%d", &n);
	}

	return 0;
}