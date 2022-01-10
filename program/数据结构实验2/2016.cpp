#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
int out;		//ȫ�ֱ���m������ʾÿ�������·����

//�������ܣ��������ݴ���һ���Թ�
void CreateMaze(int* &mazeArray, int m)
{
	mazeArray = new int[3 * m];
	if (!mazeArray) exit(OVERFLOW);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 3; j++)		//ÿ��·�ڹ̶�����������
		{
			scanf("%d", mazeArray+i*3+j);
		}
	}
}

//����·����Ϣ�Թ��ĵݹ��㷨,���ҵ�����ʱ����1����û�ҵ����ڻ��߲������ҵ�����ʱ����0
int Maze(int crossing, int *A)		
{
	if (crossing == 0) return 0;		//����·��Ϊ0ʱ�����ߣ�ֱ���߲�ͨ����˲����·�ڵ��ﲻ�˳���
	else if (crossing == out) return 1;		//����·��Ϊoutʱ����·�ڳ��ڣ�����ҵ����ڣ�����1
	if (!Maze(A[(crossing-1)*3], A) && !Maze(A[(crossing-1)* 3 + 1], A) && !Maze(A[(crossing-1) * 3 + 2], A))
	{
		return 0;			//����ǰ·�ڵĺ�������·�ڶ��߲�ͨʱ����ǰ·���߲�ͨ
	}
	else return 1;
}


int main()
{
	int* mazeArray;		//��������洢�Թ���Ϣ
	int num;		//�ֱ��ʾ·�������ͳ���λ�ã�·����ţ�
	scanf("%d", &num);
	while (num)
	{
		CreateMaze(mazeArray, num);

		scanf("%d", &out);		//��ȡ����λ��
		if (Maze(1, mazeArray))	printf("YES\n");	//ʼ�մ�һ��·�ڽ���
		else printf("NO\n");

		delete mazeArray; mazeArray = NULL;		//mazeArrayΪ��̬������ڴ棬�������Ҫ�ͷ�

		scanf("%d", &num);
	}

	return 0;
}