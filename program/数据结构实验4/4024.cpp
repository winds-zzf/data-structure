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
//	int pr = 0;		//pr、pb始终指向下一个可以插入位置
//	int pb = n - 1;
//	char temp;		//暂存取出的颜色
//	for (int i = 0; i <= pb; i++)
//	{
//		if ('R' == color[i])		//红色前移
//		{
//			temp = color[i]; color[i] = color[pr];	color[pr++] = temp;					//红色交换到pr指向的位置，指针后移pr++
//			if (i != pr) i--;
//
//		}
//		else if ('B' == color[i])	//蓝色后移
//		{
//			temp = color[i]; color[i] = color[pb];	color[pb--] = temp;					//蓝色交换到pb指向的位置，指针前移pb--		
//			if (i != pb)  i--;
//		}
//		//白色不做处理
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
void Exchange(char& x, char& y)	//注意引用符号&，形参变化，改变实参
{
    char t;
    t = x;
    x = y;
    y = t;
}
void Sort(char c[], int n)	 //对砾石调整RWB，依次遍历，时间复杂度为O(1)
{
    int i = 0, j = 0, k = n - 1;        	 //从左往右依次检查砾石c[j]
    while (j <= k)                	 //c[i]左边都是R，c[k]右边都是B。R,B放对位置，W也就对了
    {
        if (c[j] == 'R')            //c[j]是R                
        {
            Exchange(c[j], c[i]); //并入左边R区域
            i++;                 //指针i后移
            if (j < i)
                j = i;
        }
        else if (c[j] == 'B')       //c[j]是B
        {
            Exchange(c[j], c[k]); //并入右边B区域
            k--;                 //指针k前移
        }
        else
            j++;                 //不需交换，指针后移
    }
}
int main()
{
    int n, i;
    while (cin >> n && n != 0)
    {
        char c[100];
        for (i = 0; i < n; i++)
            cin >> c[i];      	 //输入砾石的编号
        Sort(c, n);            	 //调整排序
        for (i = 0; i < n - 1; i++)
            cout << c[i] << " ";
        cout << c[n - 1] << endl;      //区分空格和回车
    }
    return 0;
}
