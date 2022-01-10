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
	int  data;			//结点数据域
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
		printf("%d ", p->data);
		p = p->next;		//指针后移
	}
	printf("%d\n", p->data);
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
Status CreateList_R(LinkList& L, int n)
{
	LinkList pr, pt;		//尾结点指针，始终指向尾结点；临时指针
	L = new LNode;
	if (!L) exit(LOVERFLOW);
	L->next = NULL;

	pr = L;		//尾插先指向头结点，便于插入首元结点
	for (int i = 0; i < n; i++)
	{
		pt = new LNode; if (!pt) exit(LOVERFLOW);		//申请新结点并初始化数据域;
		scanf_s("%d", &pt->data);

		pr->next = pt; pt->next = NULL; pr = pt;		//要注意左后移动尾结点位置
	}
	return OK;
}

int FindMain(LinkList &L)
{
	LinkList p, pre, q;
	int  counter, flag = ListLength(L)/2;
	p = L->next;		//p初始位置为首元结点

	while (p && p->next)		//删除最后一个结点会导致p为空，这时应该结束
	{
		counter = 1;
		pre = p;
		q = p->next;
		while (q)
		{
			if (q->data != p->data)
			{
				pre = q;
				q = q->next;
			}
			else
			{
				pre->next = q->next;
				delete q;
				q = pre->next;
				counter++;     //每有一个重复的，计数器减一
			}
		}
		if (counter > flag)  return p->data;
		else 
		{
			p = p->next;		//准备处理下一项
		}
	}
	return -1;
}

int main()
{
	int n;
	LinkList L;

	scanf_s("%d", &n);		//读入A， B的长度
	do
	{
		CreateList_R(L, n);			//初始化A、B链表

		printf("%d\n", FindMain(L));
		DestoryList(L);
		scanf_s("%d", &n);	//读入A， B的长度

	} while (n != 0);

	return 0;
}