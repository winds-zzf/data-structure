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

void CreateList_U(LinkList& L, int n)
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
		pre = L;                //��ʼ��pre��q���ֱ�ָ��ͷָ�����Ԫ���
		q = L->next;

		while (q && q->date < s->date)
		{
			pre = q;
			q = q->next;
		}

		if (q && q->date == s->date)      //������ظ�Ԫ�أ�ֱ���ͷ��½�����ڴ�
		{
			delete s;
		}
		else
		{
			s->next = q;  //�˳�ѭ��ʱ��s->date����С��q�Ķ�����pre��
			pre->next = s;
		}
	}
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
	printf("\n");
	return OK;
}

//�������ܣ���������������������ظ��ϲ�
void MergeList(LinkList& LA, LinkList& LB)
{
	LinkList pa, pb, pc, pt;        //paΪ����LA�Ľ��λ��ָ�룬pbΪ����LB�Ľ��λ��ָ�룬pcʼ��Ϊ�±��β���ָ��, pt��pointer temp�����ڼĴ��ɾ������ַ
	pa = LA->next; pb = LB->next;      //��ʼʱ�ֱ�ָ��LA�� LB��Ԫ���
	pc = LA;                //��Ԫ���λ��ҲҪ����

	while (pa && pb)
	{
		if (pa->date < pb->date)
		{
			pc->next = pa;      //���ӵ���С���
			pc = pa;            //�����½��
			pa = pa->next;      //�ƶ����λ��ָ��
		}
		else if (pa->date > pb->date)
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
		else                //�ڵ��ظ�
		{
			pc->next = pa;  pc = pa;  pa = pa->next;     //��LAΪĸ�����ظ���LA��£

			pt = pb;  pb = pb->next; delete pt;     //ɾ�����̣��Ĵ�->�ƶ�->ɾ��
		}
	}
	pc->next = pa ? pa : pb;
	delete LB;      //ɾ��LB��ͷ���
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
		CreateList_U(A, n_A);			//��ʼ��A��B����
		CreateList_U(B, n_B); 
		MergeList(A, B);
		ListTraverse(A);
		DestoryList(A);					//A�ٴ�ʹ��ǰҪ����
		scanf_s("%d%d", &n_A, &n_B);	//����A�� B�ĳ���
	} while (n_A!=0||n_B!=0); 

	return 0;
}