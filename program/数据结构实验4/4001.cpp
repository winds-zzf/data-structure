#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 32767		//定义32767为无穷大
#define MVNum  	100		//最大图顶点数100
typedef char VexType;		//顶点类型为char型
typedef int ArcType;		//边类型为int型
typedef int Status;

typedef struct
{
	VexType vexs[MVNum];			//顶点表
	ArcType arcs[MVNum][MVNum];		//邻接矩阵
	int vexnum, arcnum;				//图当前顶点数和边数
}AMGraph;		//定义图的邻接矩阵表示

//获取顶点在顶点集中的序号及邻接矩阵坐标
int LocateVex(AMGraph G, VexType v1)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v1) return i;
	}
	return -1;
}

//基于邻接矩阵创建有向网G
Status CreateDN_AMG(AMGraph& G)
{
	int w;		//边权值
	char v1, v2;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);		//读入总顶点数和边数，为输入顶点和边做准备

	for (int i = 0; i < G.vexnum; i++)			//根据总顶点数，依次输入所有顶点信息
		scanf_s(" %c", &G.vexs[i], 1);

	for (int i = 0; i < G.vexnum; i++)			//初始化邻接矩阵网，全为无穷大MaxInt
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = MaxInt;

	for (int k = 0, i, j; k < G.arcnum; k++)		//根据总边数，依次输入所有边信息
	{
		scanf_s(" %c %c%d", &v1, 1, &v2, 1, &w);
		i = LocateVex(G, v1); j = LocateVex(G, v2);	//获取边顶点序号，已确定边在邻接矩阵中的坐标（i，j）
		G.arcs[i][j] = w;
	}
	return OK;
}

//修改版迪杰斯特拉算法：当找到目的点即终止算法，输出路径，并返回结果
void ShortestPath_DIJ(AMGraph G, VexType src, VexType dst)
{//基于邻接矩阵的dijkstra算法
	int v0, v1, n = G.vexnum;		//总顶点数
	int S[MVNum];			//S数组为状态数组，已访问过为true，否则为false
	int D[MVNum];			//D数组存储从起点到i对应点的当前最短距离
	int Path[MVNum];		//Path数组存储i对应顶点当前的直接前驱结点，若无值为-1，否则为对应顶点序号
	char pathVex[MVNum];		//存储路径信息；
	int p = -1;
	/*----------初始化三个辅助数组Path[],S[], D[]-------*/
	v0 = LocateVex(G, src); v1 = LocateVex(G, dst);
	for (int i = 0; i < n; i++)
	{
		D[i] = G.arcs[v0][i];		//初始化D数组，初始为v0到其余各点的距离
		S[i] = false;				//初始化状态数组S，标记未访问的所有点
		if (D[i] < MaxInt) Path[i] = v0;	//v0到其余各点可达，记录直接前驱为v0，否则无直接前驱，值-1
		else Path[i] = -1;
	}
	D[v0] = 0; S[v0] = true;	//v0->v0距离为0，v0已被访问

	/*------初始化完成，开始查找v0到各点(n-1个)的最短路径--------*/
	for (int i = 1, k = 0, min; i < n; i++)
	{
		min = MaxInt;					//查找本轮最短路径顶点k
		for (int j = 0; j < n; j++)
			if (!S[j] && D[j] < min) { k = j; min = D[j]; }	//由于k初始为MaxInt，因此k=j一定至少执一次

		//根据新确定永久顶点k，更新辅助数组
		S[k] = true;		//记为永久标记
		for (int i = 0; i < n; i++)
		{//如果说经过k点到i点的距离比当前到i点距离断，则更新为从k出发, 路径长度为从v0经k到i的距离
			if (!S[i] && (D[k] + G.arcs[k][i] < D[i])) { D[i] = D[k] + G.arcs[k][i], Path[i] = k; }
		}
		if (k == v1) break;		//如果已经找到终点直接退出循环
	}

	//仅输出指定路径
	printf("%d\n", D[v1]);
	while (v1 != v0)			//前驱结点不为起始点，继续循环
	{
		pathVex[++p] = G.vexs[v1];		//直接存入字符
		v1 = Path[v1];
	}
	printf("%c ", G.vexs[v0]);
	while (p > 0)
	{
		printf("%c ", pathVex[p--]);
	}
	printf("%c\n", pathVex[p]);
}

int main()
{
	VexType src, dst;
	AMGraph G;
	CreateDN_AMG(G);		//触发循环
	while (G.vexnum || G.arcnum)			//当顶点数边数全为零时结束循环
	{
		scanf_s(" %c %c", &src, 1, &dst, 1);	//读入起始点src与终点dst
		ShortestPath_DIJ(G, src, dst);	//迪杰斯特拉算法稍作修改版本

		CreateDN_AMG(G);
	}
	return 0;
}