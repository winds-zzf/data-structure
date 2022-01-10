#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 32767		//����32767Ϊ�����
#define MVNum  	100		//���ͼ������100
typedef int VexType;		//��������Ϊchar��
typedef int ArcType;		//������Ϊint��
typedef int Status;

typedef struct
{
	VexType vexs[MVNum];			//�����
	ArcType arcs[MVNum][MVNum];		//�ڽӾ���
	int vexnum, arcnum;				//ͼ��ǰ�������ͱ���
}AMGraph;		//����ͼ���ڽӾ����ʾ

//��ȡ�����ڶ��㼯�е���ż��ڽӾ�������
int LocateVex_AM(AMGraph G, VexType v1)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v1) return i;
	}
	return -1;
}

//�����ڽӾ��󴴽�������G
Status CreateUDN_AMG(AMGraph& G)
{
	int w;		//��Ȩֵ
	VexType v1, v2;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);		//�����ܶ������ͱ�����Ϊ���붥��ͱ���׼��

	for (int i = 0; i < G.vexnum; i++)			//�����ܶ������������������ж�����Ϣ
		G.vexs[i] = i + 1;
			
	for (int i = 0; i < G.vexnum; i++)			//��ʼ���ڽӾ�������ȫΪ�����MaxInt
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = MaxInt;

	for (int k = 0; k < G.arcnum; k++)		//�����ܱ����������������б���Ϣ
	{
		scanf_s("%d%d%d", &v1, &v2, &w);
		G.arcs[v1-1][v2-1] = G.arcs[v2 - 1][v1 - 1] = w;
	}
	return OK;
}

//�޸İ�Ͻ�˹�����㷨�����ҵ�Ŀ�ĵ㼴��ֹ�㷨�����·���������ؽ��
void ShortestPath_DIJ(AMGraph G, int v0)
{//�����ڽӾ����dijkstra�㷨
	int v, n = G.vexnum;			//��������n		
	int S[MVNum];				//S���鼴Ϊ״̬���飬�ѷ��ʹ��Ľ��ֵΪTrue������Ϊfalse
	int D[MVNum];				//D����洢��ʼ�㵽i��Ӧ��ĵ�ǰ��̾���
	int Path[MVNum];			//Path[]�洢���Ϊi�Ķ����ǰ����㣬���û��ֱ��ǰ����ֵΪ���ֵ-1

	/*---------------------------------------��ʼ��������������----------------------------------*/
	for (int i = 0; i < n; i++)
	{
		S[i] = false;						//��ʼ��Ϊδ���ñ��
		D[i] = G.arcs[v0][i];				//��ʼ��Ϊ��ʼ��v0���������ľ���
		if (D[i] < MaxInt)	Path[i] = v0;	//v0��i��ľ���С���������v0�ɴ�i��i��ֱ��ǰ��Ϊv0��	
		else Path[i] = -1;					//v0��i�ľ���Ϊ�����v0��i���ɴ�
	}
	D[v0] = 0;						//��ʼ�㵽����ľ���Ϊ0;
	S[v0] = true;					//��ʼ�������ѷ���

	/*--------------------------------��ʼ��������ʼ���㵽�������ľ���-------------------------*/
	for (int i = 1, min, v; i < n; i++)	//������v0��ʣ��n-1���������̾��루i����ѭ������������
	{
		//���ң����ұ��ֵ����·��
		min = MaxInt;						//��ʼ��minΪ����������Сֵ
		v = v0;								//vҪ��ʼ��v0,���򵱳���v0Ϊ������ʱ��v��Ϊ���ֵ
		for (int j = 0; j < n; j++)
		{														//������δ��ȷ�����Ľ���������·��!S[j] && D[j]<min
			if (!S[j] && D[j] < min) { min = D[j]; v = j; }		//v����Ҫ���ȳ�ʼ��,��Ϊmin��ʼֵ��MaxIntִ�е�v = j;�Ǳ�Ȼ��
		}

		//ˢ�£������ҵ���v�����¸���������Ϣ����ǵ㣬���·����ֱ��ǰ��
		S[v] = true;
		for (int i = 0; i < n; i++)		//��kˢ��D[]��Path[]������δ���ñ�ǵĶ���
		{
			if (!S[i] && D[v] + G.arcs[v][i] < D[i])	//����:������ȷ����ˢ�µ�ǰ���·���������v0��k�����·�� + v��i�ľ���ȵ�ǰ���·��С���򾭹�vֱ�ӵ�i����
			{
				D[i] = D[v] + G.arcs[v][i];		//�����·��Ϊ0-v-i��
				Path[i] = v;					//��k��i������iֱ��ǰ���޸�Ϊv
			}
		}
	}

	v = v0;					//k��ʼ��Ϊ���v0
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
	CreateUDN_AMG(G);		//����ѭ��
	while (G.vexnum || G.arcnum)			//������������ȫΪ��ʱ����ѭ��
	{
		scanf_s("%d", &src);			//������ʼ��src���յ�dst
		ShortestPath_DIJ(G, src-1);	//�Ͻ�˹�����㷨�����޸İ汾

		CreateUDN_AMG(G);
	}
	return 0;
}