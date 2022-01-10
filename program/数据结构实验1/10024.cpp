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
Status InitList(LinkList L)
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

//�������ظ����������󽻼�
void DifferentSet(LinkList& LA, LinkList& LB)
{
	LinkList pa, pb, pt, pc;		//���λ��ָ��,��ʱָ�룬����βָ��
	pa = LA->next; pb = LB->next;			//����Ԫ��㿪ʼ����
	pc = LA;		//βָ���ʼָ��ͷ���

	while (pa && pb)
	{
		if (pa->date == pb->date)
		{
			pc->next = pa->next; delete pa; pa = pc->next;			//LA��ֻ�漰����ɾ������

			pt = pb; pb = pb->next;	delete pt;
		}
		else if (pa->date < pb->date)
		{
			pc = pa;  pa = pa->next;  		//paС����һ������Ĵ��
		}
		else
		{
			pt = pb; pb = pb->next; delete pt;
		}
	}
	while (pb)     //pa��pbβ����NULL���õ������,ע���󽻼��������������
	{
		pt = pb; pb = pb->next; delete pt;
	}
	delete LB;					//���Ǻϲ���Ҫɾ����һ����ͷ���
}

int main()
{
	LinkList A, B;
	int n_A, n_B;
	scanf_s("%d%d", &n_A, &n_B);		//����A�� B�ĳ���
	do
	{
		CreateList_R(A, n_A);			//��ʼ��A��B����
		CreateList_R(B, n_B);
		DifferentSet(A, B);
		ListTraverse(A);
		printf("%d\n", ListLength(A));
		DestoryList(A);					//A�ٴ�ʹ��ǰҪ����
		scanf_s("%d%d", &n_A, &n_B);	//����A�� B�ĳ���
	} while (n_A != 0 || n_B != 0);

	return 0;
}