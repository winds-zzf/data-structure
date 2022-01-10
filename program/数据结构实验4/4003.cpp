#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define MVNum 100			//图最大顶点数
typedef int VexType;		//顶点类型
typedef int ArcType;		//边类型
typedef struct
{
	int weight;				//边的权值
}OtherInfo;					//边的附加信息：权值等
typedef struct ArcNode
{
	int adjvex;				//邻接点序号
	OtherInfo info;			//边的其他信息
	struct ArcNode* nextarc;//下一条邻接边信息
}ArcNode;					//边结点
typedef struct 
{
	VexType data;			//存储顶点符号
	ArcNode* firstarc;		//指向第一个邻接点
}VNode, AdjList[MVNum];		//定义表头结点VNode，和表头结点表AdjList
typedef struct
{
	AdjList vertices;		//表头结点表
	int vexnum, arcnum;
}ALGraph;					//定义邻接表类型

//基于邻接表创建无向图
void CreateUDG_AL(ALGraph &G)
{
	VexType v1, v2;
	ArcNode* p;									//暂存新生成边结点
	scanf_s("%d%d", &G.vexnum, &G.arcnum);		//输入当前图的总顶点数和总边数

	for (int i = 0; i < G.vexnum; i++)
	{
		G.vertices[i].data = i+1;
		G.vertices[i].firstarc = NULL;			//初始化表头节点表
	}

	for (int i = 0; i < G.arcnum; i++)			//依次输入各条边的信息
	{
		scanf_s("%d%d", &v1, &v2);

		p = new ArcNode;					//申请新结点并输入信息
		if (!p) exit(OVERFLOW);
		p->adjvex = v2-1;
		p->nextarc = G.vertices[v1 - 1].firstarc;		//前插法存入新边结点
		G.vertices[v1 - 1].firstarc = p;

		p = new ArcNode;					//申请新结点并输入信息
		if (!p) exit(OVERFLOW);
		p->adjvex = v1-1;
		p->nextarc = G.vertices[v2 - 1].firstarc;		//前插法存入新边结点
		G.vertices[v2 - 1].firstarc = p;
	}
}

//函数功能：插入新的邻接边
void InsertArcNode(ALGraph &G, VexType v0)
{
	G.vertices[G.vexnum].data = v0;
	G.vertices[G.vexnum++].firstarc = NULL;			//在最后一位后面加入新结点，顶点数加一
}

//输出邻接表
void Output_AL(ALGraph G)
{
	ArcNode* p;
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("%d", G.vertices[i].data);
		p = G.vertices[i].firstarc;
		if (p)
		{
			while (p)
			{
				printf(" %d", G.vertices[p->adjvex].data);		//输出临接边信息，并移动指针指向下一位
				p = p->nextarc;
			}
		}
		printf("\n");
	}
}

int main()
{
	ALGraph G;
	VexType v0;

	CreateUDG_AL(G);
	while (G.vexnum || G.arcnum)
	{
		scanf_s("%d" ,&v0);
		InsertArcNode(G, v0);
		Output_AL(G);
		CreateUDG_AL(G);
	}

	return 0;
}