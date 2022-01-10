#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdlib.h>
#include<stdio.h>
#define MaxInt 32767		//����32767Ϊ�����
#define MVNum	100			//ͼ��󶥵���Max ventex number
typedef int VexType;		//ͼ��������Ϊchar
typedef int ArcType;		//ͼ������Ϊint
typedef int Status;			//����Status��ʾ״̬

typedef struct
{
	VexType vexs[MVNum];		//�����
	ArcType arcs[MVNum][MVNum];	//�ڽӾ���(�߹�ϵ)
	int vexnum, arcnum;			//ͼ��ǰ������������
}AMGraph;			//�ڽӾ����ʾͼ�ṹ

//
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

//�������ܣ������µ��ڽӱ�
void InsertArcNode(AMGraph& G, VexType v1, VexType v2)
{
	G.arcs[v1 - 1][v2 - 1] = G.arcs[v2 - 1][v1 - 1] = 1;					//����ͼ��ע�ⲻ��������
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