#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
typedef int Status;
typedef struct
{
	char bookNum[15];	//书号
	char bookName[40];	//书名
	float bookPrice;	//书籍价格
}Book;			//定义Book类型结构体变量存储书籍信息
typedef struct LNode
{
	Book date;			//结点数据域
	struct LNode* next;	//结点指针域
}LNode, * LinkList;

//结构体数据输入
void Input(Book& e)
{
	scanf("%s%s%f",
		e.bookNum, 15,
		e.bookName, 40,
		&e.bookPrice
	);
}

//结构体数组数据输出
void Output(Book e)
{
	printf("%s %s %.2f\n",
		e.bookNum,
		e.bookName,
		e.bookPrice
	);
}

//比较两个结构体是否相同
Status BookCmp(Book elem_1, Book elem_2)
{
	if (!strcmp(elem_1.bookNum, elem_2.bookNum))
	{
		if (!strcmp(elem_1.bookName, elem_2.bookName))
		{
			if (fabs((double)elem_1.bookPrice - (double)elem_2.bookPrice) < 0.0001)
				return OK;
		}
	}
	return ERROR;
}//线性链表初始化

Status InitList(LinkList& L)
{
	L = new LNode;		//申请新节点作为头结点
	if (!L) exit(LOVERFLOW);

	L->next = NULL;	//空表指针域为空
	return OK;
}

//线性链表遍历
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //结点位置指针
	if (!L->next) return ERROR;		//遍历要判断链表是否为空
	while (p)
	{
		Output(p->date);
		p = p->next;		//指针后移
	}
	return OK;
}

//前插法创建单链表
Status CreateList_R(LinkList& L, int n)
{
	LinkList p, t;		//尾指针p, 临时结点指针r，寄存新生成结点地址
	Book e;

	L = new LNode; if (!L) exit(LOVERFLOW);		//创建一个空表，并判断是否成功
	L->next = NULL;

	p = L;		//头插法开始时指向头指针
	for (int i = 0; i < n; i++)
	{
		t = new LNode;			//申请一个新结点,并输入数据
		if (!t) exit(LOVERFLOW);
		Input(e);	t->date = e;

		p->next = t; t->next = NULL; p = t;		//尾插法有个尾指针，一直在只想尾结点
	}
	return OK;
}

//图书信息降序存储
Status CreateList_D(LinkList& L, int n)
{
	LinkList pre, q, t;  //定位指针， 临时指针
	Book e;		//存储结点数据

	L = new LNode; if (!L) exit(OVERFLOW); L->next = NULL;		//创建一个空表
	for (int i = 0; i < n; i++)
	{
		pre = L; q = L->next;		//在每一次输入查找前，初始化位置指针

		Input(e);
		while (q && q->date.bookPrice >= e.bookPrice)
		{
			pre = q; q = q->next;		//位置指针后移
		}

		t = new LNode; if (!t) exit(OVERFLOW); t->date = e;	//申请新结点并初始化；

		pre->next = t; t->next = q;		//插入新结点
	}
	return OK;
}

//搜寻最爱书籍
Status SearchList(LinkList L, Book e)
{
	LinkList p;		//结点位置指针
	int counter = 0;	//计数器
	if (!L->next) return ERROR;

	p = L->next;
	while (p)
	{
		if (!strcmp(p->date.bookName, e.bookName)) counter++;
		p = p->next;
	}

	if (counter == 0) printf("Sorry，there is no your favourite!\n");
	else
	{
		printf("%d\n", counter);
		p = L->next;		//p重新指向初始位置
		while (p)
		{
			if (!strcmp(p->date.bookName, e.bookName)) Output(p->date); 
			p = p->next;
		}
	}

	return OK;
}


int main()
{
	LinkList L;
	int num, times;
	Book e;

	scanf("%d", &num);
	CreateList_R(L, num);
	scanf("%d", &times);
	for (int i = 0; i < times; i++)
	{
		scanf("%s", e.bookName, 40);
		SearchList(L, e);
	}

	return 0;
}