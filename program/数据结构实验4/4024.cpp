//#include<stdio.h>
//#include<stdlib.h>
//
//void InColor(char *color, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		scanf_s(" %c", &color[i], 1);
//	}
//}
//
//void SwapSort(char *color, int n)
//{
//	int pr = 0;		//pr��pbʼ��ָ����һ�����Բ���λ��
//	int pb = n - 1;
//	char temp;		//�ݴ�ȡ������ɫ
//	for (int i = 0; i <= pb; i++)
//	{
//		if ('R' == color[i])		//��ɫǰ��
//		{
//			temp = color[i]; color[i] = color[pr];	color[pr++] = temp;					//��ɫ������prָ���λ�ã�ָ�����pr++
//			if (i != pr) i--;
//
//		}
//		else if ('B' == color[i])	//��ɫ����
//		{
//			temp = color[i]; color[i] = color[pb];	color[pb--] = temp;					//��ɫ������pbָ���λ�ã�ָ��ǰ��pb--		
//			if (i != pb)  i--;
//		}
//		//��ɫ��������
//	}
//}
//
//void OutColor(char* color, int n)
//{
//	printf("%c", color[0]);
//	for (int i = 1; i < n; i++)
//	{
//		printf(" %c", color[i]);
//	}
//	printf("\n");
//}
//
//int main()
//{
//	int n;
//	char color[100];
//	scanf_s("%d", &n);
//	while (n)
//	{
//		InColor(color, n);
//
//		SwapSort(color, n);
//
//		OutColor(color, n);
//
//		scanf_s("%d", &n);
//	}
//	return 0;
//}

#include<iostream>
using namespace std;
void Exchange(char& x, char& y)	//ע�����÷���&���βα仯���ı�ʵ��
{
    char t;
    t = x;
    x = y;
    y = t;
}
void Sort(char c[], int n)	 //����ʯ����RWB�����α�����ʱ�临�Ӷ�ΪO(1)
{
    int i = 0, j = 0, k = n - 1;        	 //�����������μ����ʯc[j]
    while (j <= k)                	 //c[i]��߶���R��c[k]�ұ߶���B��R,B�Ŷ�λ�ã�WҲ�Ͷ���
    {
        if (c[j] == 'R')            //c[j]��R                
        {
            Exchange(c[j], c[i]); //�������R����
            i++;                 //ָ��i����
            if (j < i)
                j = i;
        }
        else if (c[j] == 'B')       //c[j]��B
        {
            Exchange(c[j], c[k]); //�����ұ�B����
            k--;                 //ָ��kǰ��
        }
        else
            j++;                 //���轻����ָ�����
    }
}
int main()
{
    int n, i;
    while (cin >> n && n != 0)
    {
        char c[100];
        for (i = 0; i < n; i++)
            cin >> c[i];      	 //������ʯ�ı��
        Sort(c, n);            	 //��������
        for (i = 0; i < n - 1; i++)
            cout << c[i] << " ";
        cout << c[n - 1] << endl;      //���ֿո�ͻس�
    }
    return 0;
}
