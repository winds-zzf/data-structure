#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef int Status;			//��intȡ����ΪStatus

typedef union
{
	char optr;	//�����
	double opnd; //������
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

Status  EvaluateExpression(double &result);
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
		else if(top == '(')		return 'e';
		else					return '>';
		break;
	default:
		return 'e';
	}
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
Status EvaluateExpression(double &result)
{
	char ch;
	Object a, theta, b;			//��������ʱ��ʱʹ��
	Object e, waste;			//e���ڴ洢��������ݣ������ݸ��ǵķ���,waste���ڱ�ʾ����������

	LinkStack OPND, OPTR;	//�ֱ�Ϊ������ջ�������ջ
	InitStack(OPND);
	InitStack(OPTR);
	
	e.optr = '=';	Push(OPTR, e);	//��'='ѹ��ջ��
	
	scanf(" %c", &ch, 1);							//��ʼ��ȡһ���ַ���Ϊ��ʼ����,�״ζ�ȡ���Կհ��ַ�������
	if (ch == '=') return FALSE;			//�׸���ȡ�ľ���=ֱ�Ӵ��󷵻�

	while (ch != '=' || GetTop(OPTR).optr != '=')			//�����벻Ϊ��������=������ջ����Ϊ�Ⱥ�ʱ��һֱ����
	{
		if (isdigit(ch))
		{
			int flag = 1;				//flag��Ϊ��ǵ�����С����ʱ��Ϊ0
			double temp = 0.1; e.opnd = 0; ;	//��ȡ����ʼ����������
			do
			{
				if (flag)	e.opnd = e.opnd * 10 + (int)ch - 48;
				else
				{
					e.opnd = e.opnd + ((double)ch - 48) * temp;
					temp /= 10;				//ÿ������һ��С��temp����10��Ϊ��һλ��Ȩ
				}
				ch = getchar();					//��ȡ��һ������

				if (ch == '.')
				{
					flag = 0;		//������С����ʱflag���Ϊ0, �����¶���һ���ַ�
					ch = getchar();
				}
			} while (isdigit(ch));		//ѭ������ʱ��ǰ���Ų��������ַ�
			Push(OPND, e);	//��ת�����������������ջ
		}
		else
		{
			switch (Precede(GetTop(OPTR).optr, ch))				//�Ƚ�ջ��Ԫ��������ַ������ȼ�
			{
			case '<':
				e.optr = ch;
				Push(OPTR, e);
				ch = getchar();			//��ȡ��һ���ַ�
				break;
			case '>':					//�ڽ��������������ǲ���ȡ�����ݵ�
				Pop(OPTR, theta); 
				Pop(OPND, b); Pop(OPND, a);			//������ջ������ȳ��������Ҳ�����b
				waste.opnd = Operate(a.opnd, theta.optr, b.opnd);		//��ȡ������������������
				Push(OPND, waste);		//��������ѹ�������ջ
				break;
			case '=':
				Pop(OPTR, waste);		//ջ��Ԫ�س�ջ
				ch = getchar();			//�ٴζ�ȡһ��Ԫ��
				break;
			default:
				break;
			}
		}
	}
	 result = GetTop(OPND).opnd;		//���ش�����ջ���Ľ��
	 DestoryStack(OPND); DestoryStack(OPTR);
	 return OK;
}