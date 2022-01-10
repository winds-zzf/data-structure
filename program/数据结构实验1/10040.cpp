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
	int  date;			//���������
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
		printf("%d ", p->date);
		p = p->next;		//ָ�����
	}
	printf("%d\n", p->date);
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
		scanf_s("%d", &pt->date);

		pr->next = pt; pt->next = NULL; pr = pt;		//Ҫע������ƶ�β���λ��
	}
	return OK;
}


//�������ܣ�ʵ�������������ż���
void DivideList(LinkList LA)
{
	LinkList pre, q,    pr, LB;		//ѡ��ժȡ, prΪ����βָ��
	int counter;
	LB = new LNode;
	if (!LB)  exit(LOVERFLOW);
	LB->next = NULL;
	pr = LB;

	pre = LA; q = LA->next;		//��ʼ��λ������ָ��
	counter = 1;		//��Ԫ���
	while (q)
	{
		if (counter % 2)
		{
			pre = q;
			q = q->next;
		}
		else
		{
			pre->next = q->next;						//ժȡ���
			pr->next = q;   q->next = NULL; pr = q;		//β�巨
			q = pre->next;			//�ָ�pre�� q����Թ�ϵ
		}
		counter++;
	}
	pre->next = LB->next;
}

int main()
{
	int n;
	LinkList A;

	scanf_s("%d", &n);		//����A�� B�ĳ���
	do
	{
		CreateList_R(A, n);			//��ʼ��A��B����
		DivideList(A);
		
		ListTraverse(A);

		DestoryList(A);
		scanf_s("%d", &n);	//����A�� B�ĳ���

	} while (n != 0);

	return 0;
}