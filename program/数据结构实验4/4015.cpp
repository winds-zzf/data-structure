#include<stdio.h>
#include<stdlib.h>
#define MAXNUM 100

typedef struct
{
	int* R;
	int length;		//���Բ��ұ���
}SSTable;			//�������Բ��ұ�SqSearchList

int Search_Bin(SSTable ST, int key, int low, int high)
{
	int mid;
	if (low > high) return 0;
	mid = (low + high)/2;
	if (key == ST.R[mid]) return mid;		//���ҳɹ�
	else if (key < ST.R[mid]) return Search_Bin(ST, key, low, mid - 1);
	else return Search_Bin(ST, key, mid + 1, high);
}

int main()
{
	int pos, key;
	SSTable ST;		//����˳����ұ�ST

	scanf_s("%d", &ST.length);
	ST.R = new int[ST.length+1];		//���±�1��ʼ
	if (!ST.R) exit(0);
	while (ST.length)
	{
		for (int i = 0; i < ST.length; i++)		//��������
			scanf_s("%d", &ST.R[i]);
		scanf_s("%d", &key);
		pos = Search_Bin(ST, key, 1, ST.length);
		if (pos) printf("YES\n");
		else printf("NO\n");

		delete[] ST.R;			//�ͷ���һ�����ұ�Ĵ洢�ռ�
		scanf_s("%d", &ST.length);
		ST.R = new int[ST.length + 1];		//���±�1��ʼ
		if (!ST.R) exit(0);
	}

	return 0;
}