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

//判断两个二叉树相等
int TreeSame(BiTree T, BiTree S)
{
	if (!T && !S)		return 1;	//两树都为空，子树相等
	else if (T && S)								//两树都不为空，继续判断
	{
		if (T->data == S->data && TreeSame(T->lchild, S->lchild) && TreeSame(T->rchild, S->rchild))
			return 1;		//利用&&运算符的短路效果来实现条件的优先级
	}
	return 0;			//T和S之间有一个为空，一定不相等
}

int main()
{
	BiTree  T, S;

	CreateBiTree(T);		//先序遍历创建二叉树T
	getchar();
	CreateBiTree(S);		//先序遍历创建二叉树S
	getchar();
	while (1)
	{
		if (TreeSame(T, S)) printf("YES\n");
		else		printf("NO\n");

		CreateBiTree(T);		//先序遍历创建二叉树T
		getchar();
		if (T == NULL) break;	//当T根结点为空时，终止循环
		CreateBiTree(S);		//先序遍历创建二叉树S
		getchar();
	}
	return 0;
}
