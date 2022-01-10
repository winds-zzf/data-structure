#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MaxInt 32767		//����32767Ϊ�����
#define MVNum	100			//ͼ��󶥵���Max ventex number
typedef int VexType;		//ͼ��������Ϊchar
typedef int ArcType;		//ͼ������Ϊint
typedef int Status;			//����Status��ʾ״̬
Status visited[MVNum];		//����ȫ�����飬�����洢�ݹ�����еı�־����

typedef struct
{
	VexType vexs[MVNum];	//ͼ���㼯
	ArcType arcs[MVNum][MVNum];	//ͼ�ڽӾ���
	int vexnum, arcnum;		//ͼ��ǰ�ܶ��������ܱ���
}AMGraph;

//������ͼ���ڽӾ���
void CreateUDG_AM(AMGraph& G)
{
	VexType v1, v2;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);				//�����ʼ�ܶ��������ܱ���

	for (int i = 0; i < G.vexnum; i++)
		G.vexs[i] = i + 1;

	for (int i = 0; i < G.vexnum; i++)					//��ʼ���ڽӾ��󣺱�ʾͼ
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = 0;

	for (int k = 0; k < G.arcnum; k++)
	{
		scanf_s("%d%d", &v1, &v2);						//��������������������V1��V2

		G.arcs[v1 - 1][v2 - 1] = G.arcs[v2 - 1][v1 - 1] = 1;					//����ͼ��ע�ⲻ��������
	}
}

//�����ڽӾ���������������
void DFS_AM(AMGraph G, int v0)
{//v0��ʾ�������ţ�ֵΪ����-1
	printf("%d", v0+1);				//���ʲ���ǽ��
	visited[v0] = true;
	for (int i = 0; i < G.vexnum; i++)
	{		//���i��v0δ�����ʹ����ڽӵ㣬��ô������
		if (!visited[i] && G.arcs[v0][i] == 1)
		{
			printf(" ");		//���һ���ո��
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
			visited[i] = false;				//��ʼ��ȫ�ֱ�־����visited[]

		scanf_s("%d", &v0);
		DFS_AM(G, v0-1);
		printf("\n");
		CreateUDG_AM(G);
	}

	return 0;
}