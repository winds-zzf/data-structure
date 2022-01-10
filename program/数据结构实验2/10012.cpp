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

//按照降序顺序创建一个链表（自动读取）
void CreateList_D(LinkList &L)
{
	LinkList pre, q, t;		//pre和q成对使用，用于锁定插入位置，t临时结点指针，寄存临时生成的结点
	Book e, m = { "0", "0", 0.0 };

	L = new LNode;		//创建一个空链表--待插入
	if (!L) exit(0);
	L->next = NULL;

	Input(e);	//先读入e用于判断
	while (!BookCmp(e, m))
	{
		pre = L; q = L->next;		//位置查找指针，在每一次查找是都是指向头结点和首元结点

		while (q && q->date.bookPrice >= e.bookPrice)		//只要q指向的结点存在，就与输入的值进行比较
		{
			pre = q; q = q->next;		//同时后移两个指针，判断下一个位置
		}

		t = new LNode; if (!t) exit(OVERFLOW);	t->date = e;	//申请并初始化一个新结点

		pre->next = t; t->next = q;		//新结点插入在pre和q之间
		Input(e);			
	}
}
int main()
{
	LinkList L;

	CreateList_D(L);

	ListTraverse(L);
	return 0;
}