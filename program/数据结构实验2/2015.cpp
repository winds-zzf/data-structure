#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef int Status;			//��intȡ����ΪStatus

typedef struct SNode
{
	char date;		//���������
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
char GetTop(LinkStack S)
{
	if (S == NULL) exit(1);
	return  S->date;		//���������ΪObject����
}

//��ջѹ��ջ
Status Push(LinkStack& S, char e)
{
	LinkStack p;

	p = new SNode;		//����һ���½��
	if (!p) exit(OVERFLOW);
	p->date = e;

	p->next = S;	S = p;
	return OK;
}

//��ջ����ջ��Ԫ��
Status Pop(LinkStack& S, char& e)
{
	LinkStack p;

	if (S == NULL) return ERROR;
	e = S->date;
	p = S;	S = S->next;	delete p;
	return OK;
}

//�ж��Ѵ��ڵ���ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S)
{
	return S ? 0 : 1;
}

char  Precede(char top, char ch);
Status TransferExpression(void);

int main()
{

	while (TransferExpression())		//ͨ������ֵ�жϼ������Ƿ�Ϸ��� �Ϸ������������������
	{
		while(getchar() !='\n') ;
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
		if (top == '(')  return '<';
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
		else					return '>';
		break;
	default:
		return 'e';
	}
}

//�������ܣ���׺���ʽ��׺���ʽ�㷨�����ʽ����=��β��
Status TransferExpression(void)
{
	char ch, e;
	LinkStack OPTR;			//������Ҫһ��������ջ��������ֱ�����
	InitStack(OPTR);
	scanf(" %c", &ch, 1);
	if (ch == '=') return ERROR;		//����ĸΪ�Ⱥţ�ֱ���˳�

	while (ch != '=')
	{
		if (isdigit(ch))
		{
			printf("%c", ch);		//���������ֱ�����
		}
		else
		{
			if (ch == ')')					//������),��������ջ��ֱ��ջ��Ϊ������
			{
				while (GetTop(OPTR) != '(')
				{
					Pop(OPTR, e);
					printf("%c", e);
				}
				Pop(OPTR, e);		//����ջ��Ԫ�أ�(
			}
			else							//�������������������Ǵ��ھ���С�ڣ�������Ϊ����
			{
				while (!StackEmpty(OPTR) && Precede(GetTop(OPTR), ch) == '>')
				{
					Pop(OPTR, e);		//����ջ��Ԫ�أ��������ֱ���������Լ����ȼ��͵�λ��
					printf("%c", e);	//������ַ���Ҫ�����ջ�ģ�Ϊ�˷�ֹ�����ǣ���Ӧ��ʹ��ch�����ַ�
				}
				Push(OPTR, ch);			//ѭ��������������ջ
			}
		}

		ch = getchar();
	}
	while (!StackEmpty(OPTR))		//��������ʱ��һֱ��ջ
	{
		Pop(OPTR, e);
		printf("%c", e);
	}
	printf("\n");		//���������'='
	return OK;
}