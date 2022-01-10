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

//�������ܣ�������������л���
void DivideList(LinkList &LA, LinkList &LB)
{
	LinkList p, q, pt;		//pt��¼����Сֵ���ڽ���ַ�����ڽ���(������ѡ�񷨣����ǽ���������˼�¼λ�ã�����ֱ�ӽ���)
	int temp, counter = ListLength(LA) / 2;

	//���зǵݼ�����
	p = LA->next;
	while (p&&p->next)				//���漰ɾ����˲��ÿ���pΪ�յ����
	{
		pt = p;
		q = p->next;
		while (q)
		{
			if (q->data < pt->data)		//ʼ����Ҫ��min���бȽϵģ���Ϊmin�ж�̬��¼����Сֵ
			{
				pt = q;
			}
			q = q->next;		//���۴�С�����Σ����ն���Ҫ���Ƶģ���Ϊֻ�Ƚ�һ��
		}
		if (p->data != pt->data)
		{
			temp = p->data;
			p->data = pt->data;
			pt->data = temp;
		}
		p = p->next;
	}
	ListTraverse(LA);
	//�����������ʼ����
	p = LA;
	while (counter)		//��ֹʱpָ���һ�����ϵ�β���
	{
		p = p->next;
		counter--;
	}
	if (p)
	{
		LB->next = p->next;		//�Ѻ�벿�ָ�LB
		p->next = NULL;			//���м�ضϣ����Ҫ��NULL����Ϊ������
	}
}

int main()
{
	int n;
	LinkList A, B;
	InitList(A);	
	InitList(B);

	scanf_s("%d", &n);			//����A�� B�ĳ���
	do
	{
		
		CreateList_R(A, n);		//��ʼ��A��B����
		
		DivideList(A, B);

		ListTraverse(A);		//������������������
		ListTraverse(B);
			
		ClearList(A);			//��һ��������ͷ�����Ĵ洢�ռ�
		ClearList(B);

		scanf_s("%d", &n);		//����A�� B�ĳ���

	} while (n != 0);

	return 0;
}