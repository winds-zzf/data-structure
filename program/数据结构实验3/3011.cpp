#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define SMAXSIZE 200		//顺序栈存储空间的初始容量
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef int Status;
//二叉树的链式存储结构
typedef struct BiTNode
{
	char data;								//二叉树数据域
	struct BiTNode* lchild, * rchild;		//二叉树左、右子树
}BiTNode, * BiTree;							//创建二叉树结点类型BiTNode，和二叉树BiTNode

typedef struct
{
	BiTree* base;			//栈底指针，始终指向栈底元素
	BiTree* top;			//栈顶指针，始终指向栈顶元素
	int stacksize;		//栈可用最大容量，顺序栈要有容量上限
}SqStack;				//构造一个顺序栈

//初始化，构造一个空顺序栈
Status InitStack(SqStack& S)
{
	S.base = new BiTree[SMAXSIZE];		//栈底指针指向数组首地址
	if (!S.base) exit(OVERFLOW);	//申请存储空间失败

	S.top = S.base;					//栈顶指针与栈底指针重合表示空顺序栈
	S.stacksize = SMAXSIZE;			//栈可用最大容量为MAXSIZE

	return OK;
}

//从已存在的顺序栈中取栈顶元素
BiTree GetTop(SqStack& S)
{
	if (S.base == S.top) exit(1);	//如果顺序栈空，直接退出程序
	return *(S.top - 1);		//如果顺序栈不为空返回栈顶元素,栈顶指针是指向栈顶元素的下一位的，并非指向栈顶元素
}

//将新元素压入顺序栈栈顶
Status Push(SqStack& S, BiTree e)
{
	if (S.top - S.base == S.stacksize) return ERROR;	//如果栈顶指针与栈底指针差为最大空间，说明已经栈满
	*(S.top++) = e;										//先将新元素压入栈顶指针指向的空位置，随后栈顶指针后移
	return OK;
}

//从顺序栈栈顶弹出栈顶元素
Status Pop(SqStack& S, BiTree& e)
{
	if (S.base == S.top) return ERROR;		//空栈不能进行弹出操作
	e = *(--S.top);							//先将栈顶指针后移指向栈顶元素，再解引用
	return OK;
}

//函数功能根据表格比较两个运算符的优先级+ - * / = (  )
char Precede(char top, char ch)
{
	switch (ch)				//根据刚读入的字符判断应该进行何种操作
	{
	case '+':
	case '-':
		if (top == '(' || top == '=')  return '<';
		else return '>';
		break;
	case '*':
	case '/':
		if (top == '*' || top == '/' || top == ')') return '>';
		else return '<';
		break;
	case '(':
		if (top == ')') return 'e';		//表示出错
		else return '<';
		break;
	case ')':
		if (top == '(')			return '=';
		else if (top == '=')	return 'e';
		else					return '>';
		break;
	case '=':
		if (top == '=')			return '=';
		else if (top == '(')		return 'e';
		else					return '>';
		break;
	default:
		return 'e';
	}
}

//函数功能：对两个double类型数据按照相应运算符进行运算
int Operate(int lopnd, char optr, int ropnd)
{
	int result = 0;		//实数运算结果
	switch (optr)
	{
	case '+':
		result = lopnd + ropnd;
		break;
	case '-':
		result = lopnd - ropnd;
		break;
	case '*':
		result = lopnd * ropnd;
		break;
	case '/':
		if (ropnd == 0) exit(1);		//发生除零错误，直接退出
		result = lopnd / ropnd;
		break;
	default:
		break;
	}
	return result;						//最后集中返回计算结果
}

//创建表达式树结点(平凡树)
void CreateExpsNode(BiTree& T, char ch)
{
	T = new BiTNode;
	if (!T) exit(OVERFLOW);

	T->data = ch;		//分别输入结点信息
	T->lchild = T->rchild = NULL;		//左右子树初始化为空树
}

//创建表达式树(注意OPTR和EXPT两个栈的元素类型不一致，前者:char,后者:BiTree)
void InitExpsTree(BiTree& T)
{
	BiTree temp, a, b;		//temp临时指针，用于暂存新临时生成的二叉树结点位置
	char ch;

	SqStack EXPT, OPTR;		//表达式栈，存储根结点指针
	InitStack(EXPT); InitStack(OPTR);		//初始化辅助栈

	scanf(" %c", &ch);			//忽略开头可能存在的空白字符
	if (ch == '=')
	{
		T = NULL;	//若首字符为‘=’生成空树
		return;
	}

	CreateExpsNode(temp, '=');		//将=压入栈底
	Push(OPTR, temp);

	while (ch != '=' || GetTop(OPTR)->data != '=')		//读到结尾或者操作数栈为空，中止执行
	{
		if (isdigit(ch))
		{
			CreateExpsNode(temp, ch);		//将操作数以字符格式存储在新建的平凡树（叶子结点）中
			Push(EXPT, temp);
			ch = getchar();
		}
		else
		{
			switch (Precede(GetTop(OPTR)->data, ch))
			{
			case '<':				//优先级低，直接入栈，等待后续处理
				CreateExpsNode(temp, ch);	//为操作符创建一个树结点
				Push(OPTR, temp);
				ch = getchar();
				break;
			case '>':				//优先级高，先进行运算
				Pop(OPTR, T);
				Pop(EXPT, b);  Pop(EXPT, a);
				T->lchild = a; T->rchild = b;		//手动链接三个结点
				Push(EXPT, T);						//新根子树进EXPT栈，等待成为其他根子树的子树
				break;								//刚完成运算不读取新字符，因为可能会连续运算
			case '=':				//优先级相等，只有左右括号这种情况
				Pop(OPTR, temp);					//舍弃栈顶操作符，且另一半不进栈
				ch = getchar();
				break;
			default:
				break;
			}
		}
	}
}

//基于表达式二叉树的表达式求值
int EvaluateExpsTree(BiTree T)		//由返回状态判断所得结果是否合法
{
	int lvalue = 0, rvalue = 0;
	if (!T->lchild && !T->rchild)  return T->data - '0';		//叶子结点为操作数，返回该结点的数值（与数字字符等值的ASCII码）
	else
	{
		lvalue = EvaluateExpsTree(T->lchild);
		rvalue = EvaluateExpsTree(T->rchild);
		return Operate(lvalue, T->data, rvalue);		//返回计算结果
	}
}

int main()
{
	BiTree  T;
	InitExpsTree(T);		//创建表达式二叉树
	while (T)
	{
		printf("%d\n", EvaluateExpsTree(T));

		InitExpsTree(T);		//先序遍历创建二叉树
	}

	return 0;
}