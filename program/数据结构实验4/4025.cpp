//#include<stdio.h>
//#include<stdlib.h>
//
//void InputNum(int *num, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		scanf_s("%d", &num[i]);
//	}
//}
//
//void SortNum(int *src, int *dst, int n)
//{
//	for (int i = 0, h=0,r=n-1; i < n; i++)
//	{
//		if (src[i] < 0) dst[h++] = src[i];
//		else dst[r--] = src[i];
//	}
//}
//
//void OutNum(int *dst, int n)
//{
//	printf("%d", dst[0]);
//
//	for (int i = 0; i < n; i++)
//	{
//		printf(" %d", dst[i]);
//	}
//	printf("\n");
//}
//
//int main()
//{
//	int n;
//	int srcnum[50];
//	int dstnum[50];
//
//	scanf_s("%d", &n);
//	while (n)
//	{
//		InputNum(srcnum, n);
//
//		SortNum(srcnum, dstnum, n);
//
//		OutNum(dstnum, n);
//
//		scanf_s("%d", &n);
//	}
//
//	return 0;
//}

#include<iostream>
using namespace std;
void Exchange(int& x, int& y)	//ע�����÷���&���βα仯���ı�ʵ��
{
    int z;
    z = x;
    x = y;
    y = z;
}
void Divide(int a[], int n)	//����һ�Σ�ʱ�临�Ӷ�O(n)
{
    int i, j = 0;
    while (a[j] < 0)
        j++;        		//ָ��jָ����ߵ�һ������
    for (i = 1; i < n; i++)		//a[0]�������������ò���
        if (a[i] < 0 && a[i - 1] >= 0)	//����a[1]��ʼ����������������Ҳ���ò���
            Exchange(a[i], a[j]);
}
int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        int i, R[100];
        for (i = 0; i < n; i++)
            cin >> R[i];
        Divide(R, n);
        for (i = 0; i < n - 1; i++)
            cout << R[i] << " ";
        cout << R[n - 1] << endl;
    }
    return 0;
}