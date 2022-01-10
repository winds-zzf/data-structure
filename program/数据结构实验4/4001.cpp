#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 32767		//����32767Ϊ�����
#define MVNum  	100		//���ͼ������100
typedef char VexType;		//��������Ϊchar��
typedef int ArcType;		//������Ϊint��
typedef int Status;

typedef struct
{
	VexType vexs[MVNum];			//�����
	ArcType arcs[MVNum][MVNum];		//�ڽӾ���
	int vexnum, arcnum;				//ͼ��ǰ�������ͱ���
}AMGraph;		//����ͼ���ڽӾ����ʾ

//��ȡ�����ڶ��㼯�е���ż��ڽӾ�������
int LocateVex(AMGraph G, VexType v1)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v1) return i;
	}
	return -1;
}

//�����ڽӾ��󴴽�������G
Status CreateDN_AMG(AMGraph& G)
{
	int w;		//��Ȩֵ
	char v1, v2;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);		//�����ܶ������ͱ�����Ϊ���붥��ͱ���׼��

	for (int i = 0; i < G.vexnum; i++)			//�����ܶ������������������ж�����Ϣ
		scanf_s(" %c", &G.vexs[i], 1);

	for (int i = 0; i < G.vexnum; i++)			//��ʼ���ڽӾ�������ȫΪ�����MaxInt
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = MaxInt;

	for (int k = 0, i, j; k < G.arcnum; k++)		//�����ܱ����������������б���Ϣ
	{
		scanf_s(" %c %c%d", &v1, 1, &v2, 1, &w);
		i = LocateVex(G, v1); j = LocateVex(G, v2);	//��ȡ�߶�����ţ���ȷ�������ڽӾ����е����꣨i��j��
		G.arcs[i][j] = w;
	}
	return OK;
}

//�޸İ�Ͻ�˹�����㷨�����ҵ�Ŀ�ĵ㼴��ֹ�㷨�����·���������ؽ��
void ShortestPath_DIJ(AMGraph G, VexType src, VexType dst)
{//�����ڽӾ����dijkstra�㷨
	int v0, v1, n = G.vexnum;		//�ܶ�����
	int S[MVNum];			//S����Ϊ״̬���飬�ѷ��ʹ�Ϊtrue������Ϊfalse
	int D[MVNum];			//D����洢����㵽i��Ӧ��ĵ�ǰ��̾���
	int Path[MVNum];		//Path����洢i��Ӧ���㵱ǰ��ֱ��ǰ����㣬����ֵΪ-1������Ϊ��Ӧ�������
	char pathVex[MVNum];		//�洢·����Ϣ��
	int p = -1;
	/*----------��ʼ��������������Path[],S[], D[]-------*/
	v0 = LocateVex(G, src); v1 = LocateVex(G, dst);
	for (int i = 0; i < n; i++)
	{
		D[i] = G.arcs[v0][i];		//��ʼ��D���飬��ʼΪv0���������ľ���
		S[i] = false;				//��ʼ��״̬����S�����δ���ʵ����е�
		if (D[i] < MaxInt) Path[i] = v0;	//v0���������ɴ��¼ֱ��ǰ��Ϊv0��������ֱ��ǰ����ֵ-1
		else Path[i] = -1;
	}
	D[v0] = 0; S[v0] = true;	//v0->v0����Ϊ0��v0�ѱ�����

	/*------��ʼ����ɣ���ʼ����v0������(n-1��)�����·��--------*/
	for (int i = 1, k = 0, min; i < n; i++)
	{
		min = MaxInt;					//���ұ������·������k
		for (int j = 0; j < n; j++)
			if (!S[j] && D[j] < min) { k = j; min = D[j]; }	//����k��ʼΪMaxInt�����k=jһ������ִһ��

		//������ȷ�����ö���k�����¸�������
		S[k] = true;		//��Ϊ���ñ��
		for (int i = 0; i < n; i++)
		{//���˵����k�㵽i��ľ���ȵ�ǰ��i�����ϣ������Ϊ��k����, ·������Ϊ��v0��k��i�ľ���
			if (!S[i] && (D[k] + G.arcs[k][i] < D[i])) { D[i] = D[k] + G.arcs[k][i], Path[i] = k; }
		}
		if (k == v1) break;		//����Ѿ��ҵ��յ�ֱ���˳�ѭ��
	}

	//�����ָ��·��
	printf("%d\n", D[v1]);
	while (v1 != v0)			//ǰ����㲻Ϊ��ʼ�㣬����ѭ��
	{
		pathVex[++p] = G.vexs[v1];		//ֱ�Ӵ����ַ�
		v1 = Path[v1];
	}
	printf("%c ", G.vexs[v0]);
	while (p > 0)
	{
		printf("%c ", pathVex[p--]);
	}
	printf("%c\n", pathVex[p]);
}

int main()
{
	VexType src, dst;
	AMGraph G;
	CreateDN_AMG(G);		//����ѭ��
	while (G.vexnum || G.arcnum)			//������������ȫΪ��ʱ����ѭ��
	{
		scanf_s(" %c %c", &src, 1, &dst, 1);	//������ʼ��src���յ�dst
		ShortestPath_DIJ(G, src, dst);	//�Ͻ�˹�����㷨�����޸İ汾

		CreateDN_AMG(G);
	}
	return 0;
}