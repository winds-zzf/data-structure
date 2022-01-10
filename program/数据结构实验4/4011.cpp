#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MaxInt 32767		//定义32767为无穷大
#define MVNum	100			//图最大顶点数Max ventex number
typedef int VexType;		//图顶点类型为char
typedef int ArcType;		//图边类型为int
typedef int Status;			//定义Status表示状态
Status visited[MVNum];		//定义全局数组，用来存储递归过程中的标志变量

typedef struct
{
	VexType vexs[MVNum];	//图顶点集
	ArcType arcs[MVNum][MVNum];	//图邻接矩阵
	int vexnum, arcnum;		//图当前总顶点数，总边数
}AMGraph;

//创无向图的邻接矩阵
void CreateUDG_AM(AMGraph& G)
{
	VexType v1, v2;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);				//输入初始总顶点数、总边数

	for (int i = 0; i < G.vexnum; i++)
		G.vexs[i] = i + 1;

	for (int i = 0; i < G.vexnum; i++)					//初始化邻接矩阵：表示图
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = 0;

	for (int k = 0; k < G.arcnum; k++)
	{
		scanf_s("%d%d", &v1, &v2);						//读入边所依附的另个顶点V1，V2

		G.arcs[v1 - 1][v2 - 1] = G.arcs[v2 - 1][v1 - 1] = 1;					//无向图，注意不是无向网
	}
}

//基于邻接矩阵的深度优先搜索
void DFS_AM(AMGraph G, int v0)
{//v0表示顶点的序号，值为顶点-1
	printf("%d", v0+1);				//访问并标记结点
	visited[v0] = true;
	for (int i = 0; i < G.vexnum; i++)
	{		//如果i是v0未被访问过的邻接点，那么访问它
		if (!visited[i] && G.arcs[v0][i] == 1)
		{
			printf(" ");		//输出一个空格符
			DFS_AM(G, i);
		}
	}
}

int main()
{
	AMGraph G;
	VexType v0;

	CreateUDG_AM(G);
	while (G.vexnum || G.arcnum)
	{
		for (int i = 0; i < G.vexnum; i++)
			visited[i] = false;				//初始化全局标志数组visited[]

		scanf_s("%d", &v0);
		DFS_AM(G, v0-1);
		printf("\n");
		CreateUDG_AM(G);
	}

	return 0;
}