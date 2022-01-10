#pragma once
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
	int date;			//结点数据域
	struct LNode* next;	//结点指针域
}LNode, * LinkList;

//线性链表的尾插法创建
Status CreateList_R(LinkList& L, int n)
{
	LinkList p, t;		//尾指针p, 临时结点指针r，寄存新生成结点地址

	L = new LNode; if (!L) exit(LOVERFLOW);		//创建一个空表，并判断是否成功
	L->next = NULL;

	p = L;  //指向头结点位置
	for (int i = 0; i < n; i++)
	{
		t = new LNode; if (!t) exit(LOVERFLOW);		//申请一个新结点

		scanf_s("%d", &t->date); 					//读取数据，并存入新建结点

		p->next = t; t->next = NULL; p = t;				//每一次都要在插入后令尾结点指针域为空，因为不知道那次要是申请新节结点失败了链表就没有结束标志了
	}
	return OK;
}

//对有头结点的单链表升序排序
void SortList(LinkList L)
{
	LNode* p, * q, * t;
	int temp;
	if (L && L->next)		//存在两个以上结点，才有必要排序
	{
		p = L;
		while (p->next)		//链表的选择法排序
		{
			q = p->next;	//q初始为p的直接后继
			t = p;
			while (q)
			{
				if (q->date < t->date)  t = q;			//根据情况修改
				q = q->next;
			}

			if (t != p)
			{
				temp = t->date;
				t->date = p->date;
				p->date = temp;
			}					//交换t与p

			p = p->next;		//最后p指针后移
		}
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

//创建有序链表
Status CreateList_U(LinkList& L, int n)
{
	LinkList pre, q, t;  //定位指针， 临时指针
	int e;		//存储结点数据

	L = new LNode; if (!L) exit(LOVERFLOW); L->next = NULL;		//创建一个空表
	for (int i = 0; i < n; i++)
	{
		pre = L; q = L->next;		//在每一次输入查找前，初始化位置指针

		scanf_s("%d", &e);
		while (q && q->date <= e)
		{
			pre = q; q = q->next;		//位置指针后移
		}

		t = new LNode; if (!t) exit(LOVERFLOW); t->date = e;	//申请新结点并初始化；

		pre->next = t; t->next = q;		//插入新结点
	}
	return OK;
}

int main()
{
	LinkList L;
	int n;

	scanf_s("%d", &n);
	while (n)
	{
		CreateList_U(L, n);

		//		SortList(L);
		ListTraverse(L);

		ClearList(L);
		scanf_s("%d", &n);
	}

	return 0;
}