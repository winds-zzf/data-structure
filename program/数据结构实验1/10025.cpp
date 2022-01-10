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
Status InitList(LinkList &L)
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

//�������ܣ��Է����������н�������������
void SortElem(LinkList &LA, LinkList &LB, LinkList &LC)
{
	LinkList pt, pb_r, pc_r;		//��ʱָ�룬βָ��

	LB = new LNode; LC = new LNode; 
	if (!LB || !LC) exit(LOVERFLOW);		//��һ��Ϊ�վͷ���
	LB->next = LC->next = NULL;

	pb_r = LB; 
	pc_r = LC;			//β�巨��ʼλ����ͷ���λ��

	while (LA->next)
	{
		pt = LA->next; 
		LA->next = pt->next;		//ժ��LA����Ԫ��㣨������

		if (pt->date < 0)
		{
			pt->next = NULL; 
			pb_r->next = pt;
			pb_r = pt;		//β�巨���������滻���ÿգ��ƶ�
		}
		else
		{
			pt->next = NULL;
			pc_r->next = pt;
			pc_r = pt;
		}
	}

	delete LA; LA = NULL;		//�ͷ�LAͷ���,����ͷָ��Ϊ��
}

int main()
{
	int n_A;
	LinkList A, B, C;

	scanf_s("%d", &n_A);		//����A�� B�ĳ���
	do
	{
		CreateList_R(A, n_A);			//��ʼ��A��B����
		SortElem(A, B, C);

		ListTraverse(B);	ListTraverse(C);

		DestoryList(B);		DestoryList(C);		//B,C�ٴ�ʹ��ǰҪ����֮ǰ���ڴ�,����ᷢ���ڴ�й©

		scanf_s("%d", &n_A);	//����A�� B�ĳ���
	} while (n_A != 0);

	return 0;
}