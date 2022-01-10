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

//�ж��������������
int TreeSame(BiTree T, BiTree S)
{
	if (!T && !S)		return 1;	//������Ϊ�գ��������
	else if (T && S)								//��������Ϊ�գ������ж�
	{
		if (T->data == S->data && TreeSame(T->lchild, S->lchild) && TreeSame(T->rchild, S->rchild))
			return 1;		//����&&������Ķ�·Ч����ʵ�����������ȼ�
	}
	return 0;			//T��S֮����һ��Ϊ�գ�һ�������
}

int main()
{
	BiTree  T, S;

	CreateBiTree(T);		//�����������������T
	getchar();
	CreateBiTree(S);		//�����������������S
	getchar();
	while (1)
	{
		if (TreeSame(T, S)) printf("YES\n");
		else		printf("NO\n");

		CreateBiTree(T);		//�����������������T
		getchar();
		if (T == NULL) break;	//��T�����Ϊ��ʱ����ֹѭ��
		CreateBiTree(S);		//�����������������S
		getchar();
	}
	return 0;
}
