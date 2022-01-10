#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 32767		//定义32767为无穷大
#define MVNum  	100		//最大图顶点数100
typedef int VexType;		//顶点类型为char型
typedef int ArcType;		//边类型为int型
typedef int Status;

typedef struct
{
	VexType vexs[MVNum];			//顶点表
	ArcType arcs[MVNum][MVNum];		//邻接矩阵
	int vexnum, arcnum;				//图当前顶点数和边数
}AMGraph;		//定义图的邻接矩阵表示

//获取顶点在顶点集中的序号及邻接矩阵坐标
int LocateVex_AM(AMGraph G, VexType v1)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v1) return i;
	}
	return -1;
}

//基于邻接矩阵创建有向网G
Status CreateUDN_AMG(AMGraph& G)
{
	int w;		//边权值
	VexType v1, v2;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);		//读入总顶点数和边数，为输入顶点和边做准备

	for (int i = 0; i < G.vexnum; i++)			//根据总顶点数，依次输入所有顶点信息
		G.vexs[i] = i + 1;
			
	for (int i = 0; i < G.vexnum; i++)			//初始化邻接矩阵网，全为无穷大MaxInt
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = MaxInt;

	for (int k = 0; k < G.arcnum; k++)		//根据总边数，依次输入所有边信息
	{
		scanf_s("%d%d%d", &v1, &v2, &w);
		G.arcs[v1-1][v2-1] = G.arcs[v2 - 1][v1 - 1] = w;
	}
	return OK;
}

//修改版迪杰斯特拉算法：当找到目的点即终止算法，输出路径，并返回结果
void ShortestPath_DIJ(AMGraph G, int v0)
{//基于邻接矩阵的dijkstra算法
	int v, n = G.vexnum;			//顶点总数n		
	int S[MVNum];				//S数组即为状态数组，已访问过的结点值为True，否则为false
	int D[MVNum];				//D数组存储起始点到i对应点的当前最短距离
	int Path[MVNum];			//Path[]存储序号为i的顶点的前驱结点，如果没有直接前驱，值为标记值-1

	/*---------------------------------------初始化三个辅助数组----------------------------------*/
	for (int i = 0; i < n; i++)
	{
		S[i] = false;						//初始化为未永久标记
		D[i] = G.arcs[v0][i];				//初始化为起始点v0到其余各点的距离
		if (D[i] < MaxInt)	Path[i] = v0;	//v0到i点的距离小于无穷大，则v0可达i，i的直接前驱为v0；	
		else Path[i] = -1;					//v0到i的距离为无穷大，v0到i不可达
	}
	D[v0] = 0;						//起始点到自身的距离为0;
	S[v0] = true;					//起始点算作已访问

	/*--------------------------------初始化结束开始计算到其余各点的距离-------------------------*/
	for (int i = 1, min, v; i < n; i++)	//依次求v0到剩余n-1个顶点的最短距离（i仅做循环计数变量）
	{
		//查找：查找本轮的最短路径
		min = MaxInt;						//初始化min为最大便于找最小值
		v = v0;								//v要初始化v0,否则当出现v0为孤立点时，v将为随机值
		for (int j = 0; j < n; j++)
		{														//在所有未被确定过的结点中找最短路径!S[j] && D[j]<min
			if (!S[j] && D[j] < min) { min = D[j]; v = j; }		//v不需要事先初始化,因为min初始值我MaxInt执行到v = j;是必然的
		}

		//刷新：根据找到的v，更新辅助数组信息：标记点，最短路径，直接前驱
		S[v] = true;
		for (int i = 0; i < n; i++)		//用k刷新D[]，Path[]中所有未永久标记的顶点
		{
			if (!S[i] && D[v] + G.arcs[v][i] < D[i])	//核心:利用新确定点刷新当前最短路径，如果从v0到k的最短路径 + v到i的距离比当前最短路径小，则经过v直接到i更近
			{
				D[i] = D[v] + G.arcs[v][i];		//新最短路径为0-v-i；
				Path[i] = v;					//走k到i更近，i直接前驱修改为v
			}
		}
	}

	v = v0;					//k初始化为起点v0
	for (int i = 0, max = 0; i < G.vexnum; i++)			
	{
		if (D[i] > max && D[i]<MaxInt)
		{
			max = D[i];
			v = i; 
		}
	}
	printf("%d\n%d\n", G.vexs[v], D[v]);
}

int main()
{
	VexType src;
	AMGraph G;
	CreateUDN_AMG(G);		//触发循环
	while (G.vexnum || G.arcnum)			//当顶点数边数全为零时结束循环
	{
		scanf_s("%d", &src);			//读入起始点src与终点dst
		ShortestPath_DIJ(G, src-1);	//迪杰斯特拉算法稍作修改版本

		CreateUDN_AMG(G);
	}
	return 0;
}