#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1

//����������ʽ�洢�ṹ
typedef struct BiTNode
{
	int data;								//������������
	struct BiTNode* lchild, * rchild;		//��������������
}BiTNode, * BiTree;							//�����������������BiTNode���Ͷ�����BiTNode

//�������ܣ������������������
void CreateBiTree(BiTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '0') T = NULL;			//��������
	else
	{
		T = new BiTNode;
		if (!T) exit(OVERFLOW);
		T->data = ch;

		CreateBiTree(T->lchild);			//����������
		CreateBiTree(T->rchild);			//����������
	}
}

//�������ܣ�������������Ƚ����Ŀdegree[2]�±�0,1,2�ֱ��Ӧ0��1��2�Ƚ�㣨Ҫ��������ʼΪ�㣩
void CountNode(BiTree T, int* degree)
{
	if (T)
	{	//�жϸ�������
		if (!T->lchild && !T->rchild)		degree[0]++;	//����������Ϊ��������Ϊ0
		else if (T->lchild && T->rchild)	degree[2]++;	//�����������ǿ�������Ϊ2
		else								degree[1]++;	//���ҽ���һ������Ϊ��������Ϊ1
		//�ж�������������
		CountNode(T->lchild, degree);	//������������Ƚ����
		CountNode(T->rchild, degree);	//������������Ƚ����
	}
}

int main()
{
	BiTree  T;
	int degree[3];			//���볤��Ϊ��������ֱ�洢���Ƚ��
	CreateBiTree(T);		//�����������������
	while (T)
	{
		for (int i = 0; i <= 2; i++)	//��ʼ��degree[]����
		{
			degree[i] = 0;
		}
		CountNode(T, degree);			//ͳ�Ƹ��Ƚ��

		printf("%d ", degree[0]);		//1�Ƚ����
		printf("%d ", degree[1]);		//2�Ƚ����
		printf("%d\n", degree[2]);		//3�Ƚ����

		getchar();
		CreateBiTree(T);		//�����������������
	}

	return 0;
}
