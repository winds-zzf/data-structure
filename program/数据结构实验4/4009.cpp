#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define MVNum 100			//ͼ��󶥵���
typedef int VexType;		//��������
typedef int ArcType;		//������
typedef struct
{
	int weight;				//�ߵ�Ȩֵ
}OtherInfo;					//�ߵĸ�����Ϣ��Ȩֵ��
typedef struct ArcNode
{
	int adjvex;				//�ڽӵ����
	OtherInfo info;			//�ߵ�������Ϣ
	struct ArcNode* nextarc;//��һ���ڽӱ���Ϣ
}ArcNode;					//�߽��
typedef struct
{
	VexType data;			//�洢�������
	ArcNode* firstarc;		//ָ���һ���ڽӵ�
}VNode, AdjList[MVNum];		//�����ͷ���VNode���ͱ�ͷ����AdjList
typedef struct
{
	AdjList vertices;		//��ͷ����
	int vexnum, arcnum;
}ALGraph;					//�����ڽӱ�����

//�����ڽӱ�������ͼ
void CreateUDG_AL(ALGraph& G)
{
	VexType v1, v2;
	ArcNode* p;									//�ݴ������ɱ߽��
	scanf_s("%d%d", &G.vexnum, &G.arcnum);		//���뵱ǰͼ���ܶ��������ܱ���

	for (int i = 0; i < G.vexnum; i++)
	{
		G.vertices[i].data = i + 1;
		G.vertices[i].firstarc = NULL;			//��ʼ����ͷ�ڵ��
	}

	for (int i = 0; i < G.arcnum; i++)			//������������ߵ���Ϣ
	{
		scanf_s("%d%d", &v1, &v2);

		p = new ArcNode;					//�����½�㲢������Ϣ
		if (!p) exit(OVERFLOW);
		p->adjvex = v2 - 1;
		p->nextarc = G.vertices[v1 - 1].firstarc;		//ǰ�巨�����±߽��
		G.vertices[v1 - 1].firstarc = p;

		p = new ArcNode;					//�����½�㲢������Ϣ
		if (!p) exit(OVERFLOW);
		p->adjvex = v1 - 1;
		p->nextarc = G.vertices[v2 - 1].firstarc;		//ǰ�巨�����±߽��
		G.vertices[v2 - 1].firstarc = p;
	}
}

//����ڽӱ�
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
				printf(" %d", G.vertices[p->adjvex].data);		//����ٽӱ���Ϣ�����ƶ�ָ��ָ����һλ
				p = p->nextarc;
			}
		}
		printf("\n");
	}
}

//�������ܣ������µ��ڽӱ�
void DeleteArcNode(ALGraph& G, VexType v0, VexType v1)
{
	ArcNode* p, * pt;

	p = G.vertices[v0-1].firstarc;
	if (!p) return;	
	else if (v1 - 1 == p->adjvex)
	{
		G.vertices[v0-1].firstarc = p->nextarc;
		delete p;
	}
	else
	{
		while (p->nextarc)
		{
			if (v1 - 1 == p->nextarc->adjvex)					//��v0Ϊֱ�Ӻ�̵ı߽��ҲҪɾ��
			{
				pt = p->nextarc;
				p->nextarc = pt->nextarc;
				break;
			}
			else
			{
				p = p->nextarc;
			}
		}
	}

	p = G.vertices[v1 - 1].firstarc;
	if (!p) return;
	else if (v0 - 1 == p->adjvex)
	{
		G.vertices[v1 - 1].firstarc = p->nextarc;
		delete p;
	}
	else
	{
		while (p->nextarc)
		{
			if (v0 - 1 == p->nextarc->adjvex)					//��v0Ϊֱ�Ӻ�̵ı߽��ҲҪɾ��
			{
				pt = p->nextarc;
				p->nextarc = pt->nextarc;
				break;
			}
			else
			{
				p = p->nextarc;
			}
		}
	}

}

int main()
{
	ALGraph G;
	VexType v0, v1;

	CreateUDG_AL(G);
	while (G.vexnum || G.arcnum)
	{
		scanf_s("%d%d", &v0, &v1);
		DeleteArcNode(G, v0, v1);
		Output_AL(G);
		CreateUDG_AL(G);
	}

	return 0;
}