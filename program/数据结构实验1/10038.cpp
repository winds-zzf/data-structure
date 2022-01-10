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
	L = NULL;		//��ͷ���
	return OK;
}

//��巨������ѭ��������ͷ��㣩
Status CreateList_R(LinkList &L, int n)
{
	LinkList pr, pt;	

	L = new LNode;		//ͷ��㵥������
	if (!L) exit(LOVERFLOW);
	L->date = 1;
	L->next = L;

	pr = L;
	for (int i = 2; i<=n; i++)
	{
		pt = new LNode;
		if (!pt) exit(LOVERFLOW);
		pt->date = i;
		
		pt->next = L;
		pr->next = pt;
		pr = pt;
	}
	return OK;
}

//ѭ��������ı���
Status ListTraverse(LinkList L)
{
	LinkList p;
	if (!L) return ERROR;
	p = L;
	while (p->next != L)
	{
		printf("%d ", p->date);
		p = p->next;
	}
	printf("%d\n", p->date);
	return OK;
}

//�������ܣ�
void SelectNode(LinkList& L, int m)
{
	int counter;
	LinkList p, pre;		//���λ��ָ��
	pre = L;
	while (pre->next != L) pre = pre->next;	//�ҵ�βָ�룬�˳�ʱpָ��βָ��

	p = L;	counter = 1;		//ָ���һ�����
	while (p->next != p)		//����ʱֻʣ��һ�����
	{	
		if (counter % m == 0)
		{
			pre->next = p->next;
			printf("%d ", p->date);
			delete p;
			p = pre->next;
			counter++;
		}
		else
		{
			pre = p;	p = p->next;		//ÿ����ƶ�һ�Σ�counter��1
			counter++;
		}
	}
	printf("%d\n", p->date);
	delete p;	//���һ�����ҲҪɾ��
	p = L = NULL;
}
int main()
{

	int n, m;		//����n��ģm
	LinkList L;

	scanf_s("%d%d", &n, &m);				//����A�� B�ĳ���
	do
	{
		InitList(L);
		CreateList_R(L, n);			//��ʼ��A��B����
		SelectNode(L, m);
		ListTraverse(L);
		scanf_s("%d%d", &n, &m);				//����A�� B�ĳ���
	} while (n!=0 || m!=0);

	return 0;
}
