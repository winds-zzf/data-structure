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
}SqQueue;

//初始化队列，创建一个空顺序队
Status InitQueue(SqQueue& Q)
{
	Q.base = new int[QMAXSIZE];	//申请一个长度为MAXSize的顺序队列，并存储他的基地址
	if (!Q.base) exit(OVERFLOW);	//内存申请失败，退出程序
	Q.front = Q.rear = QMAXSIZE - 1;  //空队列头尾指针都为零，这里的所谓的指针全是数组下表，只不过不同下标指向特定数组元素罢了
	return OK;		//成功 返回
}

//清空一个已存在顺序队
Status ClearQueue(SqQueue& Q)
{
	Q.front = Q.rear = QMAXSIZE - 1;	//清空只需重置头尾指针为初始状态，注意由于是循环队列，所以清空必须全部初始化为零
	return OK;
}

// 顺序队入队
Status EnQueue(SqQueue& Q, int e)
{
	if (Q.rear == (Q.front - 1 + QMAXSIZE) % QMAXSIZE) return ERROR;//凡是设计指针后移都要进行模运算，因为数据是有模的
	Q.base[Q.front] = e;									//结构体数组可以直接进行赋值
	Q.front = (Q.front - 1 + QMAXSIZE) % QMAXSIZE;					//由于带有模的运算每加一，都要取余，因此要单独进行取余运算，不可合并
	return OK;
}

// 顺序队出队
Status DeQueue(SqQueue& Q, int& e)
{
	if (Q.front == Q.rear) return ERROR;		//出队循环队列不能为空；
	e = Q.base[Q.rear];					//取结构体数组队头元素：出队
	Q.rear = (Q.rear - 1 + QMAXSIZE) % QMAXSIZE;		//循环队列是单方向的所以头尾指针只能向后移动，又由于是具有模的运算，只要增加就要取余
	return OK;
}

// 遍历已经存在的顺序队
Status QueueTraverse(SqQueue Q)
{
	int p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.rear;		//从顺序队尾开始出队遍历
	while ((p - 1 + QMAXSIZE) % QMAXSIZE != Q.front)
	{
		printf("%d ", Q.base[p]);
		p = (p - 1 + QMAXSIZE) % QMAXSIZE;
	}
	printf("%d\n", Q.base[p]);

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
		QueueTraverse(Q);
		ClearQueue(Q);		//再次使用前清空队列
		scanf("%d", &m);
	}

	return 0;
}
