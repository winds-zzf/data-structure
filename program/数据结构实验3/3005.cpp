#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define QMAXSIZE 120
typedef int Status;

//二叉树的链式存储结构
typedef struct BiTNode
{
	int data;								//二叉树数据域
	struct BiTNode* lchild, * rchild;		//二叉树左、右子树
}BiTNode, * BiTree;							//创建二叉树结点类型BiTNode，和二叉树BiTNode

typedef struct
{
	BiTree* base;		//结构体数组基地址
	int front;		//头指针
	int rear;		//尾指针
}SqQueue;			//顺序栈

//初始化队列，创建一个空顺序队
Status InitQueue(SqQueue& Q)
{
	Q.base = new BiTree[QMAXSIZE];	//申请一个长度为MAXSize的顺序队列，并存储他的基地址
	if (!Q.base) exit(OVERFLOW);	//内存申请失败，退出程序
	Q.front = Q.rear = 0;  //空队列头尾指针都为零，这里的所谓的指针全是数组下表，只不过不同下标指向特定数组元素罢了
	return OK;		//成功 返回
}

// 获取顺序队队头元素
BiTree GetFront(SqQueue Q)
{
	if (Q.rear != Q.front) 		//如果顺序对不为空，直接读取对头元素
		return Q.base[Q.front];		//头指针直接指向对头元素，尾指针指向队尾元素的后一位，有利于直接读取和入队
}

// 顺序队入队
Status EnQueue(SqQueue& Q, BiTree e)
{
	if (Q.front == (Q.rear + 1) % QMAXSIZE) return ERROR;//凡是设计指针后移都要进行模运算，因为数据是有模的
	Q.base[Q.rear] = e;									//结构体数组可以直接进行赋值
	Q.rear = (Q.rear + 1) % QMAXSIZE;					//由于带有模的运算每加一，都要取余，因此要单独进行取余运算，不可合并
	return OK;
}

// 顺序队出队
Status DeQueue(SqQueue& Q, BiTree& e)
{
	if (Q.front == Q.rear) return ERROR;		//出队循环队列不能为空；
	e = Q.base[Q.front];					//取结构体数组队头元素：出队
	Q.front = (Q.front + 1) % QMAXSIZE;		//循环队列是单方向的所以头尾指针只能向后移动，又由于是具有模的运算，只要增加就要取余
	return OK;
}

// 判断顺序队列是否为空队
Status QueueEmpty(SqQueue Q)
{
	return Q.front == Q.rear ? 1 : 0;  //注意循环队列队与堆满是有区别的，只要头尾指针重合就说明是空队
}


//函数功能：先序遍历创建二叉树
void CreateBiTree(BiTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '0') T = NULL;			//创建空树
	else
	{
		T = new BiTNode;
		if (!T) exit(OVERFLOW);
		T->data = ch;

		CreateBiTree(T->lchild);			//创建左子树
		CreateBiTree(T->rchild);			//创建右子树
	}
}

//函数功能：计算二叉树宽度
int BiTWidth(BiTree T)
{
	int counter, max = 0;	//最大值初始化为零
	BiTree q, w;
	SqQueue QT;		//存储根子树结点的指针
	InitQueue(QT);

	//初始化层序遍历队列
	EnQueue(QT, T);		//树根指针入队头
	EnQueue(QT, NULL);	//空指针入栈作为行结束符

	//开始计数
	while (!QueueEmpty(QT) && GetFront(QT) != NULL)	//队非空说明未遍历完
	{
		counter = 0;	//初始化结点计数器为零
		while (GetFront(QT) != NULL)		//队头非空，出队，新元素入队
		{

			DeQueue(QT, q); counter++;		//双亲结点数加一
			if (q->lchild)		EnQueue(QT, q->lchild);		//
			if (q->rchild)		EnQueue(QT, q->rchild);		//
		}
		DeQueue(QT, q);		//结束符出栈
		EnQueue(QT, NULL);		//下一层遍历完后添加结束符NULL
		if (max < counter)	max = counter;		//max总是刷新为最大值
	}
	return max;
}

int main()
{
	BiTree  T;

	CreateBiTree(T);		//先序遍历创建二叉树
	while (T)
	{
		printf("%d\n", BiTWidth(T));
		getchar();
		CreateBiTree(T);		//先序遍历创建二叉树
	}

	return 0;
}
