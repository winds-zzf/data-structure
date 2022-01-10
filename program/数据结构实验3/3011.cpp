#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define SMAXSIZE 200		//˳��ջ�洢�ռ�ĳ�ʼ����
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef int Status;
//����������ʽ�洢�ṹ
typedef struct BiTNode
{
	char data;								//������������
	struct BiTNode* lchild, * rchild;		//��������������
}BiTNode, * BiTree;							//�����������������BiTNode���Ͷ�����BiTNode

typedef struct
{
	BiTree* base;			//ջ��ָ�룬ʼ��ָ��ջ��Ԫ��
	BiTree* top;			//ջ��ָ�룬ʼ��ָ��ջ��Ԫ��
	int stacksize;		//ջ�������������˳��ջҪ����������
}SqStack;				//����һ��˳��ջ

//��ʼ��������һ����˳��ջ
Status InitStack(SqStack& S)
{
	S.base = new BiTree[SMAXSIZE];		//ջ��ָ��ָ�������׵�ַ
	if (!S.base) exit(OVERFLOW);	//����洢�ռ�ʧ��

	S.top = S.base;					//ջ��ָ����ջ��ָ���غϱ�ʾ��˳��ջ
	S.stacksize = SMAXSIZE;			//ջ�����������ΪMAXSIZE

	return OK;
}

//���Ѵ��ڵ�˳��ջ��ȡջ��Ԫ��
BiTree GetTop(SqStack& S)
{
	if (S.base == S.top) exit(1);	//���˳��ջ�գ�ֱ���˳�����
	return *(S.top - 1);		//���˳��ջ��Ϊ�շ���ջ��Ԫ��,ջ��ָ����ָ��ջ��Ԫ�ص���һλ�ģ�����ָ��ջ��Ԫ��
}

//����Ԫ��ѹ��˳��ջջ��
Status Push(SqStack& S, BiTree e)
{
	if (S.top - S.base == S.stacksize) return ERROR;	//���ջ��ָ����ջ��ָ���Ϊ���ռ䣬˵���Ѿ�ջ��
	*(S.top++) = e;										//�Ƚ���Ԫ��ѹ��ջ��ָ��ָ��Ŀ�λ�ã����ջ��ָ�����
	return OK;
}

//��˳��ջջ������ջ��Ԫ��
Status Pop(SqStack& S, BiTree& e)
{
	if (S.base == S.top) return ERROR;		//��ջ���ܽ��е�������
	e = *(--S.top);							//�Ƚ�ջ��ָ�����ָ��ջ��Ԫ�أ��ٽ�����
	return OK;
}

//�������ܸ��ݱ��Ƚ���������������ȼ�+ - * / = (  )
char Precede(char top, char ch)
{
	switch (ch)				//���ݸն�����ַ��ж�Ӧ�ý��к��ֲ���
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
		if (top == ')') return 'e';		//��ʾ����
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

//�������ܣ�������double�������ݰ�����Ӧ�������������
int Operate(int lopnd, char optr, int ropnd)
{
	int result = 0;		//ʵ��������
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
		if (ropnd == 0) exit(1);		//�����������ֱ���˳�
		result = lopnd / ropnd;
		break;
	default:
		break;
	}
	return result;						//����з��ؼ�����
}

//�������ʽ�����(ƽ����)
void CreateExpsNode(BiTree& T, char ch)
{
	T = new BiTNode;
	if (!T) exit(OVERFLOW);

	T->data = ch;		//�ֱ���������Ϣ
	T->lchild = T->rchild = NULL;		//����������ʼ��Ϊ����
}

//�������ʽ��(ע��OPTR��EXPT����ջ��Ԫ�����Ͳ�һ�£�ǰ��:char,����:BiTree)
void InitExpsTree(BiTree& T)
{
	BiTree temp, a, b;		//temp��ʱָ�룬�����ݴ�����ʱ���ɵĶ��������λ��
	char ch;

	SqStack EXPT, OPTR;		//���ʽջ���洢�����ָ��
	InitStack(EXPT); InitStack(OPTR);		//��ʼ������ջ

	scanf(" %c", &ch);			//���Կ�ͷ���ܴ��ڵĿհ��ַ�
	if (ch == '=')
	{
		T = NULL;	//�����ַ�Ϊ��=�����ɿ���
		return;
	}

	CreateExpsNode(temp, '=');		//��=ѹ��ջ��
	Push(OPTR, temp);

	while (ch != '=' || GetTop(OPTR)->data != '=')		//������β���߲�����ջΪ�գ���ִֹ��
	{
		if (isdigit(ch))
		{
			CreateExpsNode(temp, ch);		//�����������ַ���ʽ�洢���½���ƽ������Ҷ�ӽ�㣩��
			Push(EXPT, temp);
			ch = getchar();
		}
		else
		{
			switch (Precede(GetTop(OPTR)->data, ch))
			{
			case '<':				//���ȼ��ͣ�ֱ����ջ���ȴ���������
				CreateExpsNode(temp, ch);	//Ϊ����������һ�������
				Push(OPTR, temp);
				ch = getchar();
				break;
			case '>':				//���ȼ��ߣ��Ƚ�������
				Pop(OPTR, T);
				Pop(EXPT, b);  Pop(EXPT, a);
				T->lchild = a; T->rchild = b;		//�ֶ������������
				Push(EXPT, T);						//�¸�������EXPTջ���ȴ���Ϊ����������������
				break;								//��������㲻��ȡ���ַ�����Ϊ���ܻ���������
			case '=':				//���ȼ���ȣ�ֻ�����������������
				Pop(OPTR, temp);					//����ջ��������������һ�벻��ջ
				ch = getchar();
				break;
			default:
				break;
			}
		}
	}
}

//���ڱ��ʽ�������ı��ʽ��ֵ
int EvaluateExpsTree(BiTree T)		//�ɷ���״̬�ж����ý���Ƿ�Ϸ�
{
	int lvalue = 0, rvalue = 0;
	if (!T->lchild && !T->rchild)  return T->data - '0';		//Ҷ�ӽ��Ϊ�����������ظý�����ֵ���������ַ���ֵ��ASCII�룩
	else
	{
		lvalue = EvaluateExpsTree(T->lchild);
		rvalue = EvaluateExpsTree(T->rchild);
		return Operate(lvalue, T->data, rvalue);		//���ؼ�����
	}
}

int main()
{
	BiTree  T;
	InitExpsTree(T);		//�������ʽ������
	while (T)
	{
		printf("%d\n", EvaluateExpsTree(T));

		InitExpsTree(T);		//�����������������
	}

	return 0;
}