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
Status CreateList_H(LinkList& L, int n)
{
	LinkList t;		//尾指针p, 临时结点指针r，寄存新生成结点地址
	Book e;

	L = new LNode; if (!L) exit(LOVERFLOW);		//创建一个空表，并判断是否成功
	L->next = NULL;

	for (int i = 0; i < n; i++)
	{
		t = new LNode;			//申请一个新结点,并输入数据
		if (!t) exit(LOVERFLOW);
		Input(e);	t->date = e;

		t->next = L->next; L->next = t;
	}
	return OK;
}

//图书信息降序存储
Status Create_Reversed(LinkList& L, int n)
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

int main()
{
	LinkList L;
	int num;

	scanf("%d", &num);
	CreateList_H(L, num);

	ListTraverse(L);

	return 0;
}