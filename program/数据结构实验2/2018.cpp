#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;
typedef struct
{
	char ch;	//存储字符
	int num;	//存储字符出现次数
}Symbol;			//定义Symbol类型结构体变量存储书籍信息
typedef struct LNode
{
	Symbol date;			//结点数据域
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

//创建有序链表
Status CreateList_U(LinkList& L)
{
	LinkList pre, q, t;  //定位指针， 临时指针
	Symbol e;		//存储结点数据

	L = new LNode; if (!L) exit(LOVERFLOW); L->next = NULL;		//创建一个空表

	scanf(" %c", &e.ch, 1);
	if (e.ch == '0') return ERROR;		//读到'0'时直接返回ERROR

	while(e.ch != '\n')	//读到换行时退出
	{
		pre = L; q = L->next;		//在每一次输入查找前，初始化位置指针

		e.num = 1;		//新创建的元素计数为1
		while (q && q->date.ch < e.ch)
		{
			pre = q; q = q->next;		//位置指针后移
		}
		if (q && q->date.ch == e.ch)
		{
			q->date.num++;		//当出现重复字符时，计数加一，新数据不插入
		}
		else
		{
			t = new LNode; if (!t) exit(LOVERFLOW); t->date = e;	//申请新结点并初始化；
			pre->next = t; t->next = q;		//插入新结点
		}
		e.ch = getchar();		//读取下一个字符
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
		printf("%c:%d\n", p->date.ch, p->date.num);
		p = p->next;		//指针后移
	}
	return OK;
}

//函数功能：对链表数据进行升序排序
int main()
{
	LinkList L;

	while (CreateList_U(L))
	{
		ListTraverse(L);
		DestoryList(L);		//用完后直接销毁， 下一次重新建表
	}
	return 0;
}