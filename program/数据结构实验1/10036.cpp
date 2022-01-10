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
	int  data;			//���������
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
		printf("%d ", p->data);
		p = p->next;		//ָ�����
	}
	printf("%d\n", p->data);
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
Status CreateList_R(LinkList& L, int n)
{
	LinkList pr, pt;		//β���ָ�룬ʼ��ָ��β��㣻��ʱָ��
	L = new LNode;
	if (!L) exit(LOVERFLOW);
	L->next = NULL;

	pr = L;		//β����ָ��ͷ��㣬���ڲ�����Ԫ���
	for (int i = 0; i < n; i++)
	{
		pt = new LNode; if (!pt) exit(LOVERFLOW);		//�����½�㲢��ʼ��������;
		scanf_s("%d", &pt->data);

		pr->next = pt; pt->next = NULL; pr = pt;		//Ҫע������ƶ�β���λ��
	}
	return OK;
}

int FindMain(LinkList &L)
{
	LinkList p, pre, q;
	int  counter, flag = ListLength(L)/2;
	p = L->next;		//p��ʼλ��Ϊ��Ԫ���

	while (p && p->next)		//ɾ�����һ�����ᵼ��pΪ�գ���ʱӦ�ý���
	{
		counter = 1;
		pre = p;
		q = p->next;
		while (q)
		{
			if (q->data != p->data)
			{
				pre = q;
				q = q->next;
			}
			else
			{
				pre->next = q->next;
				delete q;
				q = pre->next;
				counter++;     //ÿ��һ���ظ��ģ���������һ
			}
		}
		if (counter > flag)  return p->data;
		else 
		{
			p = p->next;		//׼��������һ��
		}
	}
	return -1;
}

int main()
{
	int n;
	LinkList L;

	scanf_s("%d", &n);		//����A�� B�ĳ���
	do
	{
		CreateList_R(L, n);			//��ʼ��A��B����

		printf("%d\n", FindMain(L));
		DestoryList(L);
		scanf_s("%d", &n);	//����A�� B�ĳ���

	} while (n != 0);

	return 0;
}