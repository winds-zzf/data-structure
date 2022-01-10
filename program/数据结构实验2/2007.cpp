#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;

typedef struct QNode
{
	int date;
	struct QNode* next;		//结点数据域
}QNode, * LinkQueue;			//定义队列结点

//函数功能：初始化循环链队（设置头结点，以及尾指针）
Status InitQueue(LinkQueue& Q)
{
	Q = new QNode;
	if (!Q) exit(OVERFLOW);
	Q->next = Q;			//循环队列初始时指向自己
	return OK;
}

//函数功能：循环链队入队
Status EnQueue(LinkQueue &Q, int e)
{
	LinkQueue pt;

	pt = new QNode;
	if (!Q) exit(OVERFLOW);
	pt->date = e;

	pt->next = Q->next;
	Q->next = pt;		//要连接前后两部分，然后再移动Q
	Q = pt;

	return OK;
}

//函数功能：循环链队出队
Status DeQueue(LinkQueue &Q, int &e)
{
	LinkQueue pt;
	if (Q->next == Q) return ERROR;				//队列为空
	pt = Q->next->next; 
	if (pt != Q)		Q->next->next = pt->next;
	else
	{
		Q = Q->next;
		Q->next = Q;
	}
	e = pt->date;		//传值
	return OK;
}

//函数功能：判断队列是否为空
Status QueueEmpty(LinkQueue Q)
{
	return Q->next == Q ? TRUE : FALSE;
}

//清空循环链队
Status ClearQueue(LinkQueue &Q)
{
	LinkQueue pt;

	while (Q->next != Q)
	{
		pt = Q->next->next;		//寄存移动删除
		if (pt != Q)		Q->next->next = pt->next;
		else
		{
			Q = Q->next;
			Q->next = Q;
		}
		delete pt;
	}

	return OK;
}


int main()
{
	LinkQueue Q;
	InitQueue(Q);
	int m, n, e;

	scanf("%d%d", &m, &n);
	while (m!=0 || n!=0)
	{
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &e);
			EnQueue(Q, e);		//读取并入队
		}
		for (int i = 0; i < n; i++)
		{
			DeQueue(Q, e);
			printf("%d ", e);
		}
		printf("%d\n", !QueueEmpty(Q));
		ClearQueue(Q);		//再次使用前要进行清空操作
		scanf("%d%d", &m, &n);
	}

	return 0;
}
