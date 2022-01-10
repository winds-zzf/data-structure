#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
int out;		//全局变量m用来表示每次输入的路口数

//函数功能：根据数据创建一个迷宫
void CreateMaze(int* &mazeArray, int m)
{
	mazeArray = new int[3 * m];
	if (!mazeArray) exit(OVERFLOW);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 3; j++)		//每个路口固定有三个出口
		{
			scanf("%d", mazeArray+i*3+j);
		}
	}
}

//基于路口信息迷宫的递归算法,当找到出口时返回1，当没找到出口或者不可能找到出口时返回0
int Maze(int crossing, int *A)		
{
	if (crossing == 0) return 0;		//当该路口为0时不用走，直接走不通，因此不会此路口到达不了出口
	else if (crossing == out) return 1;		//当该路口为out时，该路口出口，因此找到出口，返回1
	if (!Maze(A[(crossing-1)*3], A) && !Maze(A[(crossing-1)* 3 + 1], A) && !Maze(A[(crossing-1) * 3 + 2], A))
	{
		return 0;			//当当前路口的后续三个路口都走不通时，当前路口走不通
	}
	else return 1;
}


int main()
{
	int* mazeArray;		//定义数组存储迷宫信息
	int num;		//分别表示路口数量和出口位置（路口序号）
	scanf("%d", &num);
	while (num)
	{
		CreateMaze(mazeArray, num);

		scanf("%d", &out);		//读取出口位置
		if (Maze(1, mazeArray))	printf("YES\n");	//始终从一号路口进入
		else printf("NO\n");

		delete mazeArray; mazeArray = NULL;		//mazeArray为动态申请的内存，用完后需要释放

		scanf("%d", &num);
	}

	return 0;
}