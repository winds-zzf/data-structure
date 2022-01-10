#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdlib.h>
#include<stdio.h>
#define MaxInt 32767		//����32767Ϊ�����
#define MVNum	100			//ͼ��󶥵���Max ventex number
typedef char VexType;		//ͼ��������Ϊchar
typedef int ArcType;		//ͼ������Ϊint
typedef int Status;			//����Status��ʾ״̬
Status visited[MVNum];		//����ȫ�����飬�����洢�ݹ�����еı�־����
int flag;					//ȫ�ֱ��

typedef struct
{
	int weigth;
}OtherInfo;					//�ߵ�������Ϣ
typedef struct ArcNode
{
	int adjvex;				//�ڽӵ����
	OtherInfo info;			//���ߵ�������Ϣ
	struct ArcNode* nextarc;	//ָ����
}ArcNode;					//�߽��
typedef struct
{
	VexType data;			//�������
	ArcNode* firstarc;		//��ͷ����׸��ڽӱ�
}VNode, AdjList[MVNum];		//��ͷ���ͱ�ͷ����
typedef struct
{
	AdjList vertices;		//��ͷ����
	int vexnum, arcnum;
}ALGraph;					//�ڽӱ�

//���ݶ�����Ŷ�λ���ڽӱ��ͷ�����е����
int LocateVex_AL(ALGraph G, VexType vex)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (vex == G.vertices[i].data) return i;
	}
	return -1;		//δ�ڱ�ͷ�������ҵ����ַ�
}

Status CreateDG_AL(ALGraph& G)
{//�����ڽӱ�������ͼG
	char v1, v2;
	ArcNode* pt;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);

	for (int i = 0; i < G.vexnum; i++)		//���ݶ���������ʼ����ͷ����:������š�firstarc
	{
		scanf_s(" %c", &G.vertices[i].data, 1);
		G.vertices[i].firstarc = NULL;
	}

	for (int k = 0, i, j; k < G.arcnum; k++)		//���ݱ�����������ͷ�����ڽӱ�ÿһ����ͷ�ڵ������ŵĵ�����洢���ͷ��������Ķ��㣩
	{
		scanf_s(" %c %c", &v1, 1, &v2, 1);
		i = LocateVex_AL(G, v1); j = LocateVex_AL(G, v2);		//ת��Ϊ�ڽӱ�λ��

		pt = new ArcNode; if (!pt) exit(OVERFLOW);
		pt->adjvex = j;
		pt->nextarc = G.vertices[i].firstarc; G.vertices[i].firstarc = pt;		//ǰ�巨
	}
	return OK;
}

//�����ڽӾ���������������
void DFS_AL(ALGraph G, int v0, int v1)
{
	ArcNode* p;
	if (flag) return;		//���ҵ���ֱ�ӷ��أ����ڲ���
	visited[v0] = true;
	
	p = G.vertices[v0].firstarc;				//�ݹ�����ڽӵ�
	while (p)
	{
		if (!visited[p->adjvex])
		{
			if (p->adjvex == v1) flag = 1;		//���ҵ�flag���Ϊ1
			DFS_AL(G, p->adjvex, v1);		//���v0�ĸ��ڽӵ�δ�����ʹ���������ȱ����˽��
		}
		p = p->nextarc;			
	}
}

int main()
{
	ALGraph G;
	VexType src, dst;

	CreateDG_AL(G);
	while (G.vexnum || G.arcnum)
	{
		flag = 0;							//��ʼ���Ϊδ�ҵ�
		for (int i = 0; i < G.vexnum; i++)
			visited[i] = false;				//��ʼ��ȫ�ֱ�־����visited[]

		scanf_s(" %c %c", &src, 1, &dst, 1);
		DFS_AL(G, LocateVex_AL(G, src), LocateVex_AL(G, dst));

		if (flag) printf("YES\n");
		else printf("NO\n");

		CreateDG_AL(G);
	}

	return 0;
}