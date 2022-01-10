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

void CreateList_ND(LinkList& L, int n)
{
	LinkList s, pre, q;         //s���ڼĴ��½�����ַ��pre��q���ʹ����������λ��

	L = new LNode;              //����ͷ��㣻
	if (!L) exit(LOVERFLOW);
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		s = new LNode;          //�½����ݽ��
		if (!s) exit(LOVERFLOW);
		scanf_s("%d", &s->date);

		pre = L;  q = L->next;              //��ʼ��pre��q���ֱ�ָ��ͷָ�����Ԫ���
		
		while (q && q->date <= s->date)
		{
			pre = q;
			q = q->next;
		}

		pre->next = s; 
		s->next = q;
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

//�������ܣ�����ǰ�巨ʵ�������������ظ�����ϲ�
void MergeList_R_NU(LinkList& LA, LinkList& LB)
{
	LinkList pa, pb, pt;		//LA�� LB���λ��ָ�룬ptΪ��ʱָ��
	pa = LA->next; pb = LB->next;		//pa�� pb�Ǵ���Ԫ��㿪ʼժȡ��
	LA->next = NULL;				//������ǰ�巨�����Ա�����ǰ����һ���ձ�

	while (pa && pb)
	{
		if (pa->date <= pb->date)
		{
			pt = pa; pa = pa->next;					//��ѡ�еĽ��ժ����ָ�����
		}
		else
		{
			pt = pb; pb = pb->next;					//��LB��ѡ�еĽ��ɾ��
		}
		pt->next = LA->next; LA->next = pt;		//��ժ���Ľ��ǰ�巨������ptʼ��Ϊ��ʱλ��
	}
	while (pa)
	{
		pt = pa; pa = pa->next;					//��ѡ�еĽ��ժ����ָ�����
		pt->next = LA->next; LA->next = pt;		//��ժ���Ľ��ǰ�巨������ptʼ��Ϊ��ʱλ��
	}
	while (pb)
	{
		pt = pb; pb = pb->next;
		pt->next = LA->next; LA->next = pt;
	}
	delete LB;		//ɾ��LB�ձ�ͷ���
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

int main()
{
	LinkList A, B;
	int n_A, n_B;
	scanf_s("%d%d", &n_A, &n_B);		//����A�� B�ĳ���
	do
	{
		CreateList_ND(A, n_A);			//��ʼ��A��B����
		CreateList_ND(B, n_B);
		MergeList_R_NU(A, B);
		ListTraverse(A);
		DestoryList(A);					//A�ٴ�ʹ��ǰҪ����
		scanf_s("%d%d", &n_A, &n_B);	//����A�� B�ĳ���
	} while (n_A != 0 || n_B != 0);

	return 0;
}