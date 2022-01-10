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
Status InitList(LinkList L)
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
Status CreateList_R(LinkList &L, int n)
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

//两个无重复集合链表求交集
void SameElem(LinkList &LA, LinkList &LB)
{
	LinkList pa, pb, pt ,pr;		//结点位置指针,临时指针，链表尾指针
	pa = LA->next; pb = LB->next;			//从首元结点开始处理
	pr = LA;								//后插法尾指针初始指向头结点

	while (pa && pb)
	{
		if ( pa->date == pb->date )
		{
			pt = pa; pa = pa->next;		//摘除结点
			pr->next = pt; pt->next = NULL; pr = pt;		//尾插法结构三部曲

			pt = pb; pb = pb->next; delete pt;			//寄存移动删除
		}
		else if(pa->date < pb->date)
		{
			pt = pa; pa = pa->next; delete pt;		//分别删除pa，pb指向的结点
		}
		else
		{
			pt = pb; pb = pb->next; delete pt;
		}
	}
	pt = pa ? pa : pb; 
	while (pt)     //pa，pb尾部有NULL不用单独添加,注意求交集，多出来的舍弃
	{
		pr = pt; pt = pt->next; delete pr;
	}
	delete LB;					//凡是合并，要删除另一个的头结点
}

int main()
{
	LinkList A, B;
	int n_A, n_B;
	scanf_s("%d%d", &n_A, &n_B);		//读入A， B的长度
	do
	{
		CreateList_R(A, n_A);			//初始化A、B链表
		CreateList_R(B, n_B);
		SameElem(A, B);
		ListTraverse(A);
		DestoryList(A);					//A再次使用前要销毁
		scanf_s("%d%d", &n_A, &n_B);	//读入A， B的长度
	} while (n_A != 0 || n_B != 0);

	return 0;
}