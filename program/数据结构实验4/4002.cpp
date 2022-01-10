#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*----------------------------------------------顺序队列---------------------------------------*/
#define QMAXSIZE 120
typedef struct
{
	int* base;		//结构体数组基地址
	int front;		//头指针
	int rear;		//尾指针
}SqQueue;			//顺序栈
//初始化队列，创建一个空顺序队
Status InitQueue(SqQueue& Q)
{
	Q.base = new int[QMAXSIZE];	//申请一个长度为MAXSize的顺序队列，并存储他的基地址
	if (!Q.base) exit(OVERFLOW);	//内存申请失败，退出程序
	Q.front = Q.rear = 0;  //空队列头尾指针都为零，这里的所谓的指针全是数组下表，只不过不同下标指向特定数组元素罢了
	return OK;		//成功 返回
}
//清空一个已存在顺序队
Status ClearQueue(SqQueue& Q)
{
	Q.front = Q.rear = 0;	//清空只需重置头尾指针为初始状态，注意由于是循环队列，所以清空必须全部初始化为零
	return OK;
}
// 判断顺序队列是否为空队
Status QueueEmpty(SqQueue Q)
{
	return Q.front == Q.rear ? 1 : 0;  //注意循环队列队与堆满是有区别的，只要头尾指针重合就说明是空队
}
// 顺序队入队
Status EnQueue(SqQueue& Q, int e)
{
	if (Q.front == (Q.rear + 1) % QMAXSIZE) return ERROR;//凡是设计指针后移都要进行模运算，因为数据是有模的
	Q.base[Q.rear] = e;									//结构体数组可以直接进行赋值
	Q.rear = (Q.rear + 1) % QMAXSIZE;					//由于带有模的运算每加一，都要取余，因此要单独进行取余运算，不可合并
	return OK;
}
// 顺序队出队
Status DeQueue(SqQueue& Q, int& e)
{
	if (Q.front == Q.rear) return ERROR;		//出队循环队列不能为空；
	e = Q.base[Q.front];					//取结构体数组队头元素：出队
	Q.front = (Q.front + 1) % QMAXSIZE;		//循环队列是单方向的所以头尾指针只能向后移动，又由于是具有模的运算，只要增加就要取余
	return OK;
}


/*---------------------------------------------邻接矩阵图--------------------------------------*/
#define MaxInt 32767	//MaxInt定义为无穷大
#define MVNum  100		//MVNum为图最大顶点数
typedef int VexType;	//定义顶点类型，单独定义一种类型别名，降低修改的复杂度(因为如果定义为int型修改时难以锁定修改位置)
typedef int ArcType;	//定义边类型
typedef struct
{
	VexType vexs[MVNum];		//图顶点集
	ArcType arcs[MVNum][MVNum];	//邻接矩阵
	int vexnum, arcnum;			//图当前总顶点数、总边数
}AMGraph;						//图的邻接矩阵结构
void CreateUNG_AM(AMGraph& G)
{
	VexType v1, v2;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);				//输入初始总顶点数、总边数

	for (int i = 0; i < G.vexnum; i++)					//初始化邻接矩阵：表示图
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j]=0;

	for (int k = 0; k < G.arcnum; k++)
	{
		scanf_s("%d%d", &v1, &v2);						//读入边所依附的另个顶点V1，V2
		
		G.arcs[v1-1][v2-1] = G.arcs[v2-1][v1-1] = 1;					//无向图，注意不是无向网
	}
}
void SixDegree_BFS(AMGraph G, int v0)
{//基于广度优先搜索算法的六度空间理论验证
	int visited_Num=0;						//记录路径长度不超过7的顶点数
	int visited[MVNum] = {false};			//顶点访问标记
	int level[MVNum];						//记录每一层入队的顶点个数，用于确定下一次循环次数
	SqQueue Q;  InitQueue(Q);	

	visited[true]; EnQueue(Q, v0);			//初始点入队，并标记为已访问
	level[0] = 1;							//第一层由一个顶点：起始点v0

	for (int len = 1, u; len<=6 && !QueueEmpty(Q); len++)		//最多循环六次，因此除起点以外还能广度优先搜索六层
	{
		level[len] = 0;										//第len行开始前，顶点数清零
		for (int i = 0; i < level[len-1]; i++)				//第len层循环次数是由前一层结点数level[len-1]决定的
		{
			DeQueue(Q, u);
			for (int  i = 0; i < G.vexnum; i++)				//在邻接矩阵对应行(u行)中找未被访问过(!visited[i])的邻接点(G.arcs[u][i]==1)
				if (!visited[i]&&G.arcs[u][i]==1)
				{
					visited[i] = true;
					level[len]++;							//该层顶点数加一
					visited_Num++;
					EnQueue(Q, i);
				}
		}
	}

	printf("%d:%.2f%%\n", v0, (float)visited_Num*100/G.vexnum);
}

/*---------------------------------------主函数-----------------------------------*/
int main()
{
	AMGraph G;

	CreateUNG_AM(G);
	while (G.vexnum || G.arcnum)
	{
		for (int i = 0; i < G.vexnum; i++)
		{
			SixDegree_BFS(G, i);		//依次对每一个顶点使用
		}

		CreateUNG_AM(G);
	}
	return 0;
}