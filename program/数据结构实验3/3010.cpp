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

//�������ܣ�������������
int BiTDepth(BiTree T)
{
	int m, n;
	if (!T) return 0;			//�������Ϊ��
	else
	{
		m = BiTDepth(T->lchild);	//���㵱ǰ�����������������
		n = BiTDepth(T->rchild);	//���㵱ǰ�����������������
		return m > n ? m + 1 : n + 1;	//������Ƚϴ���������ֵ�������ϵ�ǰ������һ��
	}
}

int main()
{
	BiTree  T;
	int degree[3];			//���볤��Ϊ��������ֱ�洢���Ƚ��
	CreateBiTree(T);		//�����������������
	while (T)
	{
		printf("%d\n", BiTDepth(T));
		getchar();
		CreateBiTree(T);		//�����������������
	}

	return 0;
}
