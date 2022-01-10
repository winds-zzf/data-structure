#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;

typedef struct
{
	int top[2], base[2];	//ջ����ջ��ָ��
	int *V;					//ջ������,ָ��
	int stacksize;			//ջ�����������
}SqStack;		//����һ������ΪSqStack��˳��ջ

//�������ܣ���ʼ��˫��˳��ջ
Status InitDuStack(SqStack &S, int m)
{
	S.V = new int[m];		//�����СΪm������ռ�
	if (!S.V) exit(OVERFLOW);

	S.top[0] = -1; S.base[0] = 0;
	S.top[1] = m; S.base[1] = m-1;
	S.stacksize = m;		//˳��ջ�����������Ϊm
	return OK;
}

//�������ܣ�˫ջ��ջ(select��ʾջ��ѡ��ջ0��ջ1)
Status Push(SqStack &S, int e, int select)
{
	if (S.top[0] + 1 == S.top[1]) return ERROR;
	if (select)		//ѡ��ջ1
	{
		S.V[--S.top[1]] = e;
	}
	else			//ѡ��ջ0
	{
		S.V[++S.top[0]] = e;
	}
	return OK;
}

//�������ܣ�˫ջ��ջ
Status Pop(SqStack &S, int &e, int select)
{
	if (select)		//ѡ��ջ1
	{
		if (S.top[1]-1== S.base[1]) return ERROR;
		e = S.V[S.top[1]++];
	}
	else			//ѡ��ջ0
	{
		if (S.top[0]+1 == S.base[0]) return ERROR;
		e = S.V[S.top[0]--];
	}
	return OK;
}

//�������ܣ��ж�ջ��
Status StackEmpty(SqStack S, int select)
{
	if (select)		//ѡ��ջ1
	{
		if (S.top[1] - 1 == S.base[1]) return TRUE;
		else return FALSE;
	}
	else			//ѡ��ջ0
	{
		if (S.top[0] + 1 == S.base[0]) return TRUE;
		else return FALSE;
	}
	return OK;
}

//�������ܣ����˫ջ
Status ClearStatck(SqStack &S)
{
	if (!S.V) return OK;
	delete S.V; S.V = NULL;	//�ͷ�������ڴ�ռ䣬����ʼ������ָ��
	return OK;
}

//�������ܣ��ж��Ƿ�ջջ��
Status StackFull(SqStack S)		
{
	if (S.top[0] + 1 == S.top[1]) return TRUE;
	else return FALSE;
}

int main()
{
	int m, e;
	int e0, e1, d0, d1;
	SqStack S;			//����һ��˫ջ

	scanf("%d", &m);
	do
	{		
		InitDuStack(S, m);
		scanf("%d%d%d%d", &e0, &e1, &d0, &d1);
		for (int i = 0; i < e0; i++)		//����
		{
			scanf("%d", &e);
			Push(S, e, 0);
		}
		for (int i = 0; i < e1; i++)
		{
			scanf("%d", &e);
			Push(S, e, 1);
		}
		printf("%d\n", StackFull(S));		//ջ����

		for (int i = 0; i <d0; i++)			//ɾ��
		{
			Pop(S, e, 0);
			printf("%d ", e);
		}
		printf("%d\n", !StackEmpty(S, 0));		//ջ�գ�

		for (int i = 0; i < d1; i++)
		{
			Pop(S, e, 1);
			printf("%d ", e);
		}
		printf("%d\n", !StackEmpty(S, 1));		//ջ�գ�

		ClearStatck(S);
		scanf("%d", &m);
	} while (m);



	return 0;
}