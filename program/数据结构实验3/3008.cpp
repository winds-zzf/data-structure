#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1

//二叉树的链式存储结构
typedef struct BiTNode
{
	int data;								//二叉树数据域
	struct BiTNode* lchild, * rchild;		//二叉树左、右子树
}BiTNode, * BiTree;							//创建二叉树结点类型BiTNode，和二叉树BiTNode

//函数功能：先序遍历创建二叉树
void CreateBiTree(BiTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '0') T = NULL;			//创建空树
	else
	{
		T = new BiTNode;
		if (!T) exit(OVERFLOW);
		T->data = ch;

		CreateBiTree(T->lchild);			//创建左子树
		CreateBiTree(T->rchild);			//创建右子树
	}
}

//函数功能：中序遍历二叉树
void InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);	//遍历左子树
		printf("%c", T->data);			//访问根结点
		InOrderTraverse(T->rchild);	//遍历右子树
	}
}

//函数功能：先序遍历二叉树
void PreOrderTraverse(BiTree T)
{
	if (T)
	{
		printf("%c", T->data);			//访问根结点
		PreOrderTraverse(T->lchild);	//遍历左子树
		PreOrderTraverse(T->rchild);	//遍历右子树
	}
}

//函数功能：后序遍历二叉树
void PostOrderTraverse(BiTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);	//遍历左子树
		PostOrderTraverse(T->rchild);	//遍历右子树
		printf("%c", T->data);			//访问根结点
	}
}

int main()
{
	BiTree  T;

	CreateBiTree(T);		//先序遍历创建二叉树
	while (T)
	{
		PreOrderTraverse(T);		//先序遍历
		printf("\n");
		InOrderTraverse(T);	//中序遍历
		printf("\n");
		PostOrderTraverse(T);	//后序遍历
		printf("\n");

		getchar();
		CreateBiTree(T);		//先序遍历创建二叉树
	}

	return 0;
}
