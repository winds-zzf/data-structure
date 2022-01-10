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

//函数功能：计算二叉树深度
int BiTDepth(BiTree T)
{
	int m, n;
	if (!T) return 0;			//空树深度为零
	else
	{
		m = BiTDepth(T->lchild);	//计算当前根子树左子树的深度
		n = BiTDepth(T->rchild);	//计算当前根子树右子树的深度
		return m > n ? m + 1 : n + 1;	//返回深度较大的子树深度值，并加上当前树根算一层
	}
}

int main()
{
	BiTree  T;
	int degree[3];			//申请长度为三的数组分别存储各度结点
	CreateBiTree(T);		//先序遍历创建二叉树
	while (T)
	{
		printf("%d\n", BiTDepth(T));
		getchar();
		CreateBiTree(T);		//先序遍历创建二叉树
	}

	return 0;
}
