#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdlib.h>
#include<stdio.h>
#define MaxInt 32767		//定义32767为无穷大
#define MVNum	100			//图最大顶点数Max ventex number
typedef int VexType;		//图顶点类型为char
typedef int ArcType;		//图边类型为int
typedef int Status;			//定义Status表示状态

typedef struct
{
	VexType vexs[MVNum];		//顶点表
	ArcType arcs[MVNum][MVNum];	//邻接矩阵(边关系)
	int vexnum, arcnum;			//图当前顶点数、边数
}AMGraph;			//邻接矩阵表示图结构

//
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

//函数功能：插入新的邻接边
void InsertArcNode(AMGraph& G, VexType v1, VexType v2)
{
	G.arcs[v1 - 1][v2 - 1] = G.arcs[v2 - 1][v1 - 1] = 1;					//无向图，注意不是无向网
}

//
void Output_AM(AMGraph G)
{
	int i, j, k;
	printf("0 ");
	for (k = 0; k < G.vexnum - 1; k++)
	{
		printf("%d ", G.vexs[k]);
	}
	printf("%d\n", G.vexs[k]);

	for (i = 0; i < G.vexnum; i++)
	{
		printf("%d ", G.vexs[i]);
		for (j = 0; j < G.vexnum - 1; j++)
		{
			printf("%d ", G.arcs[i][j]);
		}
		printf("%d\n", G.arcs[i][j]);
	}
}

int main()
{
	AMGraph G;
	VexType v1, v2;

	CreateUDG_AM(G);
	while (G.vexnum || G.arcnum)
	{
		scanf_s("%d%d", &v1, &v2);
		InsertArcNode(G, v1, v2);
		Output_AM(G);
		CreateUDG_AM(G);
	}

	return 0;
}