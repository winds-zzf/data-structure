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
	int  date;			//结点数据域
	struct LNode* next;	//结点指针域
}LNode, * LinkList;

//线性链表初始化
Status InitList(LinkList L)
{
	L = new LNode;
	if (!L) exit(LOVERFLOW);
	L->next = NULL;
	return OK;
}

void CreateList_ND(LinkList& L, int n)
{
	LinkList s, pre, q;         //s用于寄存新建结点地址，pre和q配合使用锁定插入位置

	L = new LNode;              //创建头结点；
	if (!L) exit(LOVERFLOW);
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		s = new LNode;          //新建数据结点
		if (!s) exit(LOVERFLOW);
		scanf_s("%d", &s->date);

		pre = L;  q = L->next;              //初始化pre和q，分别指向头指针和首元结点
		
		while (q && q->date <= s->date)
		{
			pre = q;
			q = q->next;
		}

		pre->next = s; 
		s->next = q;
	}
}

//线性链表遍历
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //结点位置指针
	if (!L->next) return ERROR;		//遍历要判断链表是否为空
	while (p->next)
	{
		printf("%d ", p->date);
		p = p->next;		//指针后移
	}
	printf("%d\n", p->date);
	return OK;
}

//函数功能：利用前插法实现两个链表有重复逆序合并
void MergeList_R_NU(LinkList& LA, LinkList& LB)
{
	LinkList pa, pb, pt;		//LA， LB结点位置指针，pt为临时指针
	pa = LA->next; pb = LB->next;		//pa， pb是从首元结点开始摘取的
	LA->next = NULL;				//由于是前插法，所以必须提前创建一个空表

	while (pa && pb)
	{
		if (pa->date <= pb->date)
		{
			pt = pa; pa = pa->next;					//将选中的结点摘除，指针后移
		}
		else
		{
			pt = pb; pb = pb->next;					//将LB中选中的结点删除
		}
		pt->next = LA->next; LA->next = pt;		//将摘除的结点前插法入链表，pt始终为临时位置
	}
	while (pa)
	{
		pt = pa; pa = pa->next;					//将选中的结点摘除，指针后移
		pt->next = LA->next; LA->next = pt;		//将摘除的结点前插法入链表，pt始终为临时位置
	}
	while (pb)
	{
		pt = pb; pb = pb->next;
		pt->next = LA->next; LA->next = pt;
	}
	delete LB;		//删除LB空表头结点
}

//线性链表销毁
Status DestoryList(LinkList& L)
{
	LinkList p;			//临时结点
	while (L)
	{
		p = L; L = L->next; delete p;		//寄存， 移动， 删除
	}
	return  OK;
}

int main()
{
	LinkList A, B;
	int n_A, n_B;
	scanf_s("%d%d", &n_A, &n_B);		//读入A， B的长度
	do
	{
		CreateList_ND(A, n_A);			//初始化A、B链表
		CreateList_ND(B, n_B);
		MergeList_R_NU(A, B);
		ListTraverse(A);
		DestoryList(A);					//A再次使用前要销毁
		scanf_s("%d%d", &n_A, &n_B);	//读入A， B的长度
	} while (n_A != 0 || n_B != 0);

	return 0;
}