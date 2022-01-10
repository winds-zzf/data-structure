#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define QMAXSIZE 100
#include<stdio.h>
#include<stdlib.h>
typedef int Status;

typedef struct
{
	int* base;			//循环队列基地址
	int front, rear;	//队列头指针，尾指针
	int tag;			//标记队列的空或者满
}SqQueue;

//函数功能：初始化循环队列
Status InitQueue(SqQueue& Q)
{
	Q.base = new int[QMAXSIZE];
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;			//头尾指针初始化指向数组首元素
	Q.tag = 0;	//tag为零表示为空顺序队
	return OK;
}

//函数功能：循环队列入队
Status EnQueue(SqQueue& Q, int e)
{
	if (Q.tag) return ERROR;		//栈满tag为1

	if ((Q.rear + 1) % QMAXSIZE == Q.front) Q.tag = 1;		//如果入队前还有一个位置，则可以入队，并且入队即满
	Q.base[Q.rear] = e;		//队尾指针指向队尾元素下一位
	Q.rear = (Q.rear + 1) % QMAXSIZE;

	return OK;
}

//函数功能：循环队列出队
Status DeQueue(SqQueue& Q, int& e)
{
	if (Q.tag == 0) return ERROR;

	if ((Q.front + 1) % QMAXSIZE == Q.rear)		Q.tag = 0;//头指针后退一位，若与尾指针重合，说明只剩一个元素，删除即空
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % QMAXSIZE;
	return OK;
}
//函数功能：判断队列是否为空
Status QueueEmpty(SqQueue Q)
{
	return !Q.tag;
}

//函数功能：遍历循环队列
Status TraverseQueue(SqQueue Q)
{
	int p;

	p = Q.front;	//初始时指向头指针位置
	while ((p + 1) % QMAXSIZE != Q.rear)
	{
		printf("%d ", Q.base[p]);
		p = (p + 1) % QMAXSIZE;		//在循环意义上指针位置
	}
	printf("%d\n", Q.base[p]);
	return OK;
}

//清空循环队列
Status ClearQueue(SqQueue& Q)
{
	Q.tag = 0;				//标记置为空
	Q.front = Q.rear = 0;	//恢复头尾指针
	return OK;
}

int main()
{
	int m, e;
	SqQueue Q;
	InitQueue(Q);

	scanf("%d", &m);
	while (m)
	{
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &e);
			EnQueue(Q, e);		//输入并入栈
		}
		TraverseQueue(Q);
		ClearQueue(Q);		//再次使用前清空队列
		scanf("%d", &m);
	}

	return 0;
}
