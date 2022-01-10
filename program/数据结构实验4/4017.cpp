#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include<stdio.h>
#include<stdlib.h>
int outdata[50];			//全局数组
int pt = -1;

//二叉树的链式存储结构
typedef struct BiTNode
{
	int data;								//二叉排序树数据域
	struct BiTNode* lchild, * rchild;		//二叉排序树左、右子树
}BSTNode, * BSTree;							//创建二叉排序树

//二叉排序树的查找
BSTree SearchBST(BSTree T, int key)
{
	if (!T) return T;			//T为空说明找不到了，一直返回T==NULL
	else if (key == T->data)	return T;		//相等说明找到，返回结点地址T
	else if (key < T->data) return SearchBST(T->lchild, key);		//key偏小，在左子树中找
	else return SearchBST(T->rchild, key);			//key偏大，在右子树中找
}

//二叉排序树的插入
void InsertBST(BSTree& T, int key)
{
	//如果二叉树中不存在该节点，那么总是能找到该位置
	if (!T)			//子树为空，说明找到插入位置
	{
		T = new BSTNode;
		if (!T) exit(OVERFLOW);
		T->data = key;
		T->lchild = T->rchild = NULL;		//新插入结点一定是叶子节点，指针与为空
	}
	else if (key < T->data)  InsertBST(T->lchild, key);
	else if (key > T->data)  InsertBST(T->rchild, key);
}

//函数功能：创建二叉排序树
void CreateBST(BSTree &T)
{
	int e, num;
	T = NULL;				//将二叉树排序初始化为空树，
	scanf_s("%d", &num);	//结点数量num

	for (int i = 0; i < num; i++)
	{
		scanf_s("%d", &e);
		InsertBST(T, e);	//将新结点插入适当位置
	}
}

//基于中序遍历查找特定数据
void InOrderTraverse(BSTree T, int key)
{
	if (T)
	{
		InOrderTraverse(T->lchild, key);
		if (T->data >= key) 
			outdata[++pt] = T->data; 
		InOrderTraverse(T->rchild, key);
	}
}

int main()
{
	BSTree T;
	int key;

	CreateBST(T);
	while (T)
	{
		pt = -1;
		scanf_s("%d", &key);
		InOrderTraverse(T, key);

		for (int i = 0; i < pt; i++)
		{
			printf("%d ", outdata[i]);
		}
		printf("%d\n", outdata[pt]);

		CreateBST(T);
	}

	return 0;
}