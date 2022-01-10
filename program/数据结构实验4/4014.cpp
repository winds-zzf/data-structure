#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdlib.h>
#include<stdio.h>
#define MaxInt 32767		//定义32767为无穷大
#define MVNum	100			//图最大顶点数Max ventex number
typedef char VexType;		//图顶点类型为char
typedef int ArcType;		//图边类型为int
typedef int Status;			//定义Status表示状态
Status visited[MVNum];		//定义全局数组，用来存储递归过程中的标志变量
int flag;					//全局标记
int pathLength = 0;				//全局路径长度

typedef struct
{
	int weigth;
}OtherInfo;					//边的其他信息
typedef struct ArcNode
{
	int adjvex;				//邻接点序号
	OtherInfo info;			//出边的其他信息
	struct ArcNode* nextarc;	//指针域
}ArcNode;					//边结点
typedef struct
{
	VexType data;			//顶点符号
	ArcNode* firstarc;		//表头结点首个邻接边
}VNode, AdjList[MVNum];		//表头结点和表头结点表
typedef struct
{
	AdjList vertices;		//表头结点表
	int vexnum, arcnum;
}ALGraph;					//邻接表

//根据顶点符号定位在邻接表表头结点表中的序号
int LocateVex_AL(ALGraph G, VexType vex)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (vex == G.vertices[i].data) return i;
	}
	return -1;		//未在表头结点表中找到该字符
}

Status CreateDG_AL(ALGraph& G, int &k)
{//基于邻接表创建有向图G
	char v1, v2;
	ArcNode* pt;

	scanf_s("%d%d%d", &G.vexnum, &G.arcnum, &k);

	for (int i = 0; i < G.vexnum; i++)		//根据顶点数，初始化表头结点表:顶点符号、firstarc
	{
		scanf_s(" %c", &G.vertices[i].data, 1);
		G.vertices[i].firstarc = NULL;
	}

	for (int k = 0, i, j; k < G.arcnum; k++)		//根据边数，建立表头结点的邻接表（每一个表头节点后面跟着的单链表存储与表头结点相连的顶点）
	{
		scanf_s(" %c %c", &v1, 1, &v2, 1);
		i = LocateVex_AL(G, v1); j = LocateVex_AL(G, v2);		//转换为邻接表位置

		pt = new ArcNode; if (!pt) exit(OVERFLOW);
		pt->adjvex = j;
		pt->nextarc = G.vertices[i].firstarc; G.vertices[i].firstarc = pt;		//前插法
	}
	return OK;
}

//基于邻接矩阵的深度优先搜索
void DFS_AL(ALGraph G, int v0, int v1, int k)
{
	ArcNode* p;
	if (flag) return;
	visited[v0] = true;		//当前结点为根，标记True，防止找子树时，再次回到根部
	pathLength++;

	p = G.vertices[v0].firstarc;				//递归访问邻接点
	while (p)
	{
		if (!visited[p->adjvex])
		{
			if (v1 == p->adjvex && pathLength == k) flag = 1;
			DFS_AL(G, p->adjvex, v1, k);		//如果v0的该邻接点未被访问过，深度优先遍历此结点
		}
		p = p->nextarc;
	}
	visited[v0] = false;						//从当前结点出发的所有路径遍历完后，解除标记，以便作为其他路径的结点m
	pathLength--;						//退出该层后长度减一;
}

int main()
{
	ALGraph G;
	VexType src, dst;
	int k;				//路径长度为k

	CreateDG_AL(G, k);
	while (G.vexnum || G.arcnum)
	{
		flag = 0;							//初始标记为未找到
		pathLength = 0;
		for (int i = 0; i < G.vexnum; i++)
			visited[i] = false;				//初始化全局标志数组visited[]

		scanf_s(" %c %c", &src, 1, &dst, 1);
		DFS_AL(G, LocateVex_AL(G, src), LocateVex_AL(G, dst), k);

		if (flag) printf("YES\n");
		else printf("NO\n");

		CreateDG_AL(G, k);
	}

	return 0;
}