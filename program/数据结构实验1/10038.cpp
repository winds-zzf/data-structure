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
Status InitList(LinkList& L)
{
	L = NULL;		//无头结点
	return OK;
}

//后插法创建单循环链表（无头结点）
Status CreateList_R(LinkList &L, int n)
{
	LinkList pr, pt;	

	L = new LNode;		//头结点单独处理
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

//循环单链表的遍历
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

//函数功能：
void SelectNode(LinkList& L, int m)
{
	int counter;
	LinkList p, pre;		//结点位置指针
	pre = L;
	while (pre->next != L) pre = pre->next;	//找到尾指针，退出时p指向尾指针

	p = L;	counter = 1;		//指向第一个结点
	while (p->next != p)		//结束时只剩有一个结点
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
			pre = p;	p = p->next;		//每向后移动一次，counter加1
			counter++;
		}
	}
	printf("%d\n", p->date);
	delete p;	//最后一个结点也要删除
	p = L = NULL;
}
int main()
{

	int n, m;		//总数n与模m
	LinkList L;

	scanf_s("%d%d", &n, &m);				//读入A， B的长度
	do
	{
		InitList(L);
		CreateList_R(L, n);			//初始化A、B链表
		SelectNode(L, m);
		ListTraverse(L);
		scanf_s("%d%d", &n, &m);				//读入A， B的长度
	} while (n!=0 || m!=0);

	return 0;
}
