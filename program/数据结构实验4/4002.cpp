#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*----------------------------------------------˳�����---------------------------------------*/
#define QMAXSIZE 120
typedef struct
{
	int* base;		//�ṹ���������ַ
	int front;		//ͷָ��
	int rear;		//βָ��
}SqQueue;			//˳��ջ
//��ʼ�����У�����һ����˳���
Status InitQueue(SqQueue& Q)
{
	Q.base = new int[QMAXSIZE];	//����һ������ΪMAXSize��˳����У����洢���Ļ���ַ
	if (!Q.base) exit(OVERFLOW);	//�ڴ�����ʧ�ܣ��˳�����
	Q.front = Q.rear = 0;  //�ն���ͷβָ�붼Ϊ�㣬�������ν��ָ��ȫ�������±�ֻ������ͬ�±�ָ���ض�����Ԫ�ذ���
	return OK;		//�ɹ� ����
}
//���һ���Ѵ���˳���
Status ClearQueue(SqQueue& Q)
{
	Q.front = Q.rear = 0;	//���ֻ������ͷβָ��Ϊ��ʼ״̬��ע��������ѭ�����У�������ձ���ȫ����ʼ��Ϊ��
	return OK;
}
// �ж�˳������Ƿ�Ϊ�ն�
Status QueueEmpty(SqQueue Q)
{
	return Q.front == Q.rear ? 1 : 0;  //ע��ѭ�����ж��������������ģ�ֻҪͷβָ���غϾ�˵���ǿն�
}
// ˳������
Status EnQueue(SqQueue& Q, int e)
{
	if (Q.front == (Q.rear + 1) % QMAXSIZE) return ERROR;//�������ָ����ƶ�Ҫ����ģ���㣬��Ϊ��������ģ��
	Q.base[Q.rear] = e;									//�ṹ���������ֱ�ӽ��и�ֵ
	Q.rear = (Q.rear + 1) % QMAXSIZE;					//���ڴ���ģ������ÿ��һ����Ҫȡ�࣬���Ҫ��������ȡ�����㣬���ɺϲ�
	return OK;
}
// ˳��ӳ���
Status DeQueue(SqQueue& Q, int& e)
{
	if (Q.front == Q.rear) return ERROR;		//����ѭ�����в���Ϊ�գ�
	e = Q.base[Q.front];					//ȡ�ṹ�������ͷԪ�أ�����
	Q.front = (Q.front + 1) % QMAXSIZE;		//ѭ�������ǵ����������ͷβָ��ֻ������ƶ����������Ǿ���ģ�����㣬ֻҪ���Ӿ�Ҫȡ��
	return OK;
}


/*---------------------------------------------�ڽӾ���ͼ--------------------------------------*/
#define MaxInt 32767	//MaxInt����Ϊ�����
#define MVNum  100		//MVNumΪͼ��󶥵���
typedef int VexType;	//���嶥�����ͣ���������һ�����ͱ����������޸ĵĸ��Ӷ�(��Ϊ�������Ϊint���޸�ʱ���������޸�λ��)
typedef int ArcType;	//���������
typedef struct
{
	VexType vexs[MVNum];		//ͼ���㼯
	ArcType arcs[MVNum][MVNum];	//�ڽӾ���
	int vexnum, arcnum;			//ͼ��ǰ�ܶ��������ܱ���
}AMGraph;						//ͼ���ڽӾ���ṹ
void CreateUNG_AM(AMGraph& G)
{
	VexType v1, v2;

	scanf_s("%d%d", &G.vexnum, &G.arcnum);				//�����ʼ�ܶ��������ܱ���

	for (int i = 0; i < G.vexnum; i++)					//��ʼ���ڽӾ��󣺱�ʾͼ
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j]=0;

	for (int k = 0; k < G.arcnum; k++)
	{
		scanf_s("%d%d", &v1, &v2);						//��������������������V1��V2
		
		G.arcs[v1-1][v2-1] = G.arcs[v2-1][v1-1] = 1;					//����ͼ��ע�ⲻ��������
	}
}
void SixDegree_BFS(AMGraph G, int v0)
{//���ڹ�����������㷨�����ȿռ�������֤
	int visited_Num=0;						//��¼·�����Ȳ�����7�Ķ�����
	int visited[MVNum] = {false};			//������ʱ��
	int level[MVNum];						//��¼ÿһ����ӵĶ������������ȷ����һ��ѭ������
	SqQueue Q;  InitQueue(Q);	

	visited[true]; EnQueue(Q, v0);			//��ʼ����ӣ������Ϊ�ѷ���
	level[0] = 1;							//��һ����һ�����㣺��ʼ��v0

	for (int len = 1, u; len<=6 && !QueueEmpty(Q); len++)		//���ѭ�����Σ���˳�������⻹�ܹ��������������
	{
		level[len] = 0;										//��len�п�ʼǰ������������
		for (int i = 0; i < level[len-1]; i++)				//��len��ѭ����������ǰһ������level[len-1]������
		{
			DeQueue(Q, u);
			for (int  i = 0; i < G.vexnum; i++)				//���ڽӾ����Ӧ��(u��)����δ�����ʹ�(!visited[i])���ڽӵ�(G.arcs[u][i]==1)
				if (!visited[i]&&G.arcs[u][i]==1)
				{
					visited[i] = true;
					level[len]++;							//�ò㶥������һ
					visited_Num++;
					EnQueue(Q, i);
				}
		}
	}

	printf("%d:%.2f%%\n", v0, (float)visited_Num*100/G.vexnum);
}

/*---------------------------------------������-----------------------------------*/
int main()
{
	AMGraph G;

	CreateUNG_AM(G);
	while (G.vexnum || G.arcnum)
	{
		for (int i = 0; i < G.vexnum; i++)
		{
			SixDegree_BFS(G, i);		//���ζ�ÿһ������ʹ��
		}

		CreateUNG_AM(G);
	}
	return 0;
}