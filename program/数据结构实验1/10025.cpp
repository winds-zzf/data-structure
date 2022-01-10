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
Status InitList(LinkList &L)
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
		printf("%d ", p->date);
		p = p->next;		//指针后移
	}
	printf("%d\n", p->date);
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
		scanf_s("%d", &pt->date);

		pr->next = pt; pt->next = NULL; pr = pt;		//要注意左后移动尾结点位置
	}
	return OK;
}

//函数功能：对非零整数序列进行正负数分类
void SortElem(LinkList &LA, LinkList &LB, LinkList &LC)
{
	LinkList pt, pb_r, pc_r;		//临时指针，尾指针

	LB = new LNode; LC = new LNode; 
	if (!LB || !LC) exit(LOVERFLOW);		//有一个为空就返回
	LB->next = LC->next = NULL;

	pb_r = LB; 
	pc_r = LC;			//尾插法初始位置在头结点位置

	while (LA->next)
	{
		pt = LA->next; 
		LA->next = pt->next;		//摘除LA的首元结点（连续）

		if (pt->date < 0)
		{
			pt->next = NULL; 
			pb_r->next = pt;
			pb_r = pt;		//尾插法三部曲，替换，置空，移动
		}
		else
		{
			pt->next = NULL;
			pc_r->next = pt;
			pc_r = pt;
		}
	}

	delete LA; LA = NULL;		//释放LA头结点,并令头指针为空
}

int main()
{
	int n_A;
	LinkList A, B, C;

	scanf_s("%d", &n_A);		//读入A， B的长度
	do
	{
		CreateList_R(A, n_A);			//初始化A、B链表
		SortElem(A, B, C);

		ListTraverse(B);	ListTraverse(C);

		DestoryList(B);		DestoryList(C);		//B,C再次使用前要回收之前的内存,否则会发生内存泄漏

		scanf_s("%d", &n_A);	//读入A， B的长度
	} while (n_A != 0);

	return 0;
}