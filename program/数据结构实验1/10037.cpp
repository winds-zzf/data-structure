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

//函数功能：对无序链表进行划分
void DivideList(LinkList &LA, LinkList &LB)
{
	LinkList p, q, pt;		//pt记录了最小值所在结点地址，便于交换(这里是选择法，不是交换法，因此记录位置，而不直接交换)
	int temp, counter = ListLength(LA) / 2;

	//进行非递减排序
	p = LA->next;
	while (p&&p->next)				//不涉及删除因此不用考虑p为空的情况
	{
		pt = p;
		q = p->next;
		while (q)
		{
			if (q->data < pt->data)		//始终是要和min进行比较的，因为min中动态记录了最小值
			{
				pt = q;
			}
			q = q->next;		//无论大小情况如何，最终都是要后移的，因为只比较一次
		}
		if (p->data != pt->data)
		{
			temp = p->data;
			p->data = pt->data;
			pt->data = temp;
		}
		p = p->next;
	}
	ListTraverse(LA);
	//排序结束，开始划分
	p = LA;
	while (counter)		//终止时p指向第一个集合的尾结点
	{
		p = p->next;
		counter--;
	}
	if (p)
	{
		LB->next = p->next;		//把后半部分给LB
		p->next = NULL;			//从中间截断，因此要加NULL，作为结束符
	}
}

int main()
{
	int n;
	LinkList A, B;
	InitList(A);	
	InitList(B);

	scanf_s("%d", &n);			//读入A， B的长度
	do
	{
		
		CreateList_R(A, n);		//初始化A、B链表
		
		DivideList(A, B);

		ListTraverse(A);		//遍历处理后的两个链表
		ListTraverse(B);
			
		ClearList(A);			//第一次用完后，释放链表的存储空间
		ClearList(B);

		scanf_s("%d", &n);		//读入A， B的长度

	} while (n != 0);

	return 0;
}