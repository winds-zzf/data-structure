#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef int Status;			//��intȡ����ΪStatus

typedef struct
{
	char optr;	//�����
	double opnd; //������
	int counter;	//���ڼ����Ų������ҵ��˼���������
}Object;

typedef struct SNode
{
	Object date;		//���������
	struct SNode* next;	//���ָ����
}SNode, * LinkStack;


//��ջ�ĳ�ʼ��
Status InitStack(LinkStack& S)
{
	S = NULL;
	return OK;
}

//��ջ������
Status DestoryStack(LinkStack& S)
{
	LinkStack p;		//��ʱλ��ָ��
	while (S)			//ֻҪS��Ϊ�գ���˵��S���滹���н��
	{
		p = S; S = S->next; delete p;		//�Ĵ棬�ƶ�.ɾ��
	}
	return OK;
}

//�Ѵ�����ջ�����
Status ClearStack(LinkStack& S)	//��ջû��ͷ��㣬�����ջ��Ҫ�޸�S
{
	LinkStack p;			//��ʱ���ָ��p�Ĵ�ջ����ɾ��Ԫ��
	if (!S) return OK;		//S==NULL˵������
	while (S)				//��Ϊs��ֱ��ָ��ջ��Ԫ�صģ����ֻҪS��Ϊ�գ���˵��ջ��Ԫ������
	{
		p = S; S = S->next; delete p;		//�Ĵ棬�ƶ���ɾ��
	}
	return OK;
}

//��ջ����ջ��Ԫ��
Object GetTop(LinkStack S)
{
	if (S == NULL) exit(1);
	return  S->date;		//���������ΪObject����
}

//��ջѹ��ջ
Status Push(LinkStack& S, Object e)
{
	LinkStack p;

	p = new SNode;		//����һ���½��
	if (!p) exit(OVERFLOW);
	p->date = e;

	p->next = S;	S = p;
	return OK;
}

//��ջ����ջ��Ԫ��
Status Pop(LinkStack& S, Object& e)
{
	LinkStack p;

	if (S == NULL) return ERROR;
	e = S->date;
	p = S;	S = S->next;	delete p;
	return OK;
}

//�ǿ���ջ�ı���
Status StackTraverse(LinkStack S)
{
	LinkStack p = S;
	if (!S) return ERROR;
	while (p)
	{
		printf("%c\t%d\t", p->date.optr, p->date.counter);
		p = p->next;
	}
	printf("\n");
	return OK;
}

//�ж��Ѵ��ڵ���ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S)
{
	return S ? 0 : 1;
}

Status ExpressionPush(LinkStack& EPSN);
Status  EvaluateExpression(double& result);
char  Precede(char top, char ch);
double Operate(double lopnd, char optr, double ropnd);

int main()
{
	double result;		//�������յĽ��
	while (EvaluateExpression(result))		//ͨ������ֵ�жϼ������Ƿ�Ϸ��� �Ϸ������������������
	{
		printf("%.2f\n", result);
		fflush(stdin);
	}
	return 0;
}

//�������ܣ�������double�������ݰ�����Ӧ�������������
double Operate(double lopnd, char optr, double ropnd)
{
	double result = 0;		//ʵ��������
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

//�������ܣ����ʽ��ֵ�㷨�����ʽ��#��β��
Status EvaluateExpression(double& result)
{	
	Object e, temp;
	Object a, theta, b;				//��ʱ���ڼ�����
	LinkStack EPSN, OPTR, OPND;		//��������ջ�ֱ����洢���ʽ���������� �����
	InitStack(EPSN);  InitStack(OPND);  InitStack(OPTR);
	
	if (!ExpressionPush(EPSN))	return ERROR;		//���ʽ��ջ,��ջʧ�ܷ���ERROR

	while (!StackEmpty(EPSN))
	{
		Pop(EPSN, e);		//��ջ������һ������
		if (!isdigit(e.optr))
		{
			e.counter = 0;		//����ջ�Ĳ���������ֵΪ��
			Push(OPTR, e);			//����������ֱ����ջ
		}
		else
		{
			temp.opnd = (double)e.optr - 48;		//����������ַ�ת��Ϊ��֮�ȴ��ʵ��
			Push(OPND, temp);
			OPTR->date.counter++;	//��ջ��Ԫ�ؼ���ֵ��һ��ջ������ջ��ָ�룩
			while(!StackEmpty(OPTR)&&GetTop(OPTR).counter==2)									//ջ��������������������
			{
				Pop(OPTR, theta);
				Pop(OPND, a); Pop(OPND, b);		//�Ҳ���������ջ�� �ȳ�ջ
				temp.opnd = Operate(a.opnd, theta.optr, b.opnd);
				Push(OPND, temp);		//��������ջ
				if(!StackEmpty(OPTR))	OPTR->date.counter++;	//��ջ��Ԫ�ؼ���ֵ��һ��ջ������ջ��ָ�룩
			} 
		}
	}
	result = GetTop(OPND).opnd;
	return OK;
}

//�������ܣ������뻺�����ı��ʽ����EPSNջ��
Status ExpressionPush(LinkStack &EPSN)
{
	Object e;				//��̬�洢������ַ�
	ClearStack(EPSN);		//ʹ��ǰ���ջ�ռ�
	scanf(" %c", &e.optr, 1);
	if (e.optr == '=')		return ERROR;		//�����ʼ�Ͷ�����'='ֱ�Ӵ��󷵻�
	while (e.optr != '=')
	{
		if (e.optr != ' ') Push(EPSN, e);		//ֻҪ���ǿո񣬾���ջ
		e.optr = getchar();		//��������ٴζ���һ���ַ�
	}
	return OK;
}