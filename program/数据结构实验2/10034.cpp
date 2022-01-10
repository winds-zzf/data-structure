#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
typedef int Status;

typedef struct LNode
{
	char  data;			//结点数据域
	struct LNode* next;	//结点指针域
}LNode, * LinkList;

//线性链表初始化
Status InitList(LinkList& L)
{
	L = new LNode;
	if (!L) exit(LOVERFLOW);
	L->next = NULL;
	return OK;
}

//线性链表遍历
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //结点位置指针
	if (!L->next) return ERROR;		//遍历要判断链表是否为空
	while (p->next)
	{
		printf("%c ", p->data);
		p = p->next;		//指针后移
	}
	printf("%c\n", p->data);
	return OK;
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

//后插法创建正序链表
Status CreateList_H(LinkList& L, int n)
{
	LinkList pt;		//尾结点指针，始终指向尾结点；临时指针

	L = new LNode;
	if (!L) exit(LOVERFLOW);
	L->next = NULL;

	for (int i = 0; i < n; i++)
	{
		pt = new LNode; if (!pt) exit(LOVERFLOW);		//申请新结点并初始化数据域;
		scanf_s(" %c", &pt->data, 1);

		pt->next = L->next;
		L->next = pt;
	}

	return OK;
}

//函数功能：合并带相同后缀的单词
char MergeSameSuffix(LinkList LA, LinkList LB)
{
	LinkList pa,pre, pb;
	pre = LA; pa = LA->next;	//初始化指针
	pb = LB->next;

	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			pre = pa; pa = pa->next;	//pa需要记录其直接前驱的信息，因此要有个pre
			pb = pb->next;		
		}
		else	//这里的不相等是建立在两个链表都不为空的基础上的，因此可区别于自然退出
		{
			break;
		}
	}
	return pre->data;
}

int main()
{
	int n_A, n_B;
	LinkList A, B;

	scanf_s("%d%d", &n_A, &n_B);		//读入A， B的长度
	do
	{
		InitList(A);
		InitList(B);

		CreateList_H(A, n_A);			//初始化A、B链表
		CreateList_H(B, n_B);

		printf("%c\n", MergeSameSuffix(A, B));
		DestoryList(A);
		DestoryList(B);

		scanf_s("%d%d", &n_A, &n_B);		//读入A， B的长度
	} while (n_A!=0 || n_B!=0);

	return 0;
}