#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#define LMAXSIZE 100
#include<stdio.h>
#include<stdlib.h>

typedef int Status;
typedef struct LNode
{
	int date;			//结点数据域
	struct LNode* next;	//结点指针域
}LNode, * LinkList;

//线性链表初始化
Status InitList(LinkList& L)
{
	L = new LNode;		//申请新节点作为头结点
	if (!L) exit(LOVERFLOW);

	L->next = NULL;	//空表指针域为空
	return OK;
}

//线性链表清空
Status ClearList(LinkList L)
{
	LinkList p;
	while (L->next)		//跳过头结点
	{
		p = L->next; L->next = p->next; delete p;		//寄存， 移动， 删除；
	}
	return OK;
}

//线性链表遍历
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //结点位置指针
	if (!L->next) return ERROR;		//遍历要判断链表是否为空
	while (p)
	{
		printf("%d ", p->date);
		p = p->next;		//指针后移
	}
	return OK;
}

//线性链表的尾插法创建
Status CreateList_R(LinkList& L, int n)
{
	LinkList p, t;		//尾指针p, 临时结点指针r，寄存新生成结点地址
	int e;

	L = new LNode; if (!L) exit(LOVERFLOW);		//创建一个空表，并判断是否成功
	L->next = NULL;

	p = L;  //指向首元结点位置
	for (int i = 0; i < n; i++)
	{
		t = new LNode; if (!t) exit(LOVERFLOW);		//申请一个新结点

		scanf("%d", &e);  t->date = e;						//读取数据，并存入新建结点

		p->next = t; t->next = NULL; p = t;				//每一次都要在插入后令尾结点指针域为空，因为不知道那次要是申请新节结点失败了链表就没有结束标志了
	}
	return OK;
}

//利用递归求求平均值
int  Sum(LinkList L)
{
	if (L) return L->date + Sum(L->next);
	else return 0;
}

//线性链表长度
int ListLength(LinkList L)
{
	LinkList p;		//结点位置指针
	int j;
	p = L->next; j = 0; //开始结点位置指针，计数器值为零，因为可能是空表
	while (p)
	{
		j++;  p = p->next;		//先判断结点是否存在，然后计数器在加一，在移向后一位
	}
	return  j;
}

int main()
{
	int m;
	LinkList A;
	InitList(A);

	scanf("%d", &m);
	while (m)
	{
		CreateList_R(A, m);
		printf("%.2f\n", Sum(A->next) / (double)ListLength(A));
		ClearList(A);
		scanf("%d", &m);
	}

	return 0;
}