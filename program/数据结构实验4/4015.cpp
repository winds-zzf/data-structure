#include<stdio.h>
#include<stdlib.h>
#define MAXNUM 100

typedef struct
{
	int* R;
	int length;		//线性查找表长度
}SSTable;			//定义线性查找表SqSearchList

int Search_Bin(SSTable ST, int key, int low, int high)
{
	int mid;
	if (low > high) return 0;
	mid = (low + high)/2;
	if (key == ST.R[mid]) return mid;		//查找成功
	else if (key < ST.R[mid]) return Search_Bin(ST, key, low, mid - 1);
	else return Search_Bin(ST, key, mid + 1, high);
}

int main()
{
	int pos, key;
	SSTable ST;		//定义顺序查找表ST

	scanf_s("%d", &ST.length);
	ST.R = new int[ST.length+1];		//从下标1开始
	if (!ST.R) exit(0);
	while (ST.length)
	{
		for (int i = 0; i < ST.length; i++)		//读入数据
			scanf_s("%d", &ST.R[i]);
		scanf_s("%d", &key);
		pos = Search_Bin(ST, key, 1, ST.length);
		if (pos) printf("YES\n");
		else printf("NO\n");

		delete[] ST.R;			//释放上一个查找表的存储空间
		scanf_s("%d", &ST.length);
		ST.R = new int[ST.length + 1];		//从下标1开始
		if (!ST.R) exit(0);
	}

	return 0;
}