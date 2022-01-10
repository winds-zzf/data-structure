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

Status CreateList_R(LinkList& L)
{
	LinkList p, t;		//尾指针p, 临时结点指针r，寄存新生成结点地址
	Book e, m = {"0", "0", 0.0};

	L = new LNode; if (!L) exit(LOVERFLOW);		//创建一个空表，并判断是否成功
	L->next = NULL;

	p = L;  //指向首元结点位置
	Input(e);
	while(!BookCmp(e, m))
	{
		t = new LNode;			//申请一个新结点,并输入数据
		if (!t) exit(LOVERFLOW); 
		t->date = e;		

		p->next = t; t->next = NULL; p = t;				//最后要有p = t；因为p要始终指向尾指针
		
		Input(e);
	}
	return OK;
}

//图书信息批量编辑
Status EditList(LinkList L)
{
	LinkList p = L->next;  //结点位置指针
	float sum = 0, aver;
	int j = 0;
	if (!L->next) return ERROR;		//遍历要判断链表是否为空
	while (p)
	{
		sum += p->date.bookPrice; j++;
		p = p->next;		//指针后移
	}
	aver = sum / j;		//求平均值
	printf("%.2f\n", aver);
	p = L->next;
	while (p)
	{
		if (p->date.bookPrice <= aver) p->date.bookPrice *= 1.2f;
		else p->date.bookPrice *= 1.1f;
		p = p->next;	//指针后移
	}
	return OK;
}

int main()
{
	LinkList L;

	CreateList_R(L);

	EditList(L);
	
	ListTraverse(L);
	return 0;
}