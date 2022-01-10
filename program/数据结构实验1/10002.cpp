#include<iostream>
#include<string>        
#include<iomanip>
using namespace std;
#define OK 1 
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 1000        
typedef struct
{
    string no;       	//编号    
    string name;	//书名
    float price;   	//价格
}Book;
typedef struct
{
    Book* elem;        //Book类型的数组指针elem
    int length;        //顺序表的表长
}SqList;
int InitList_Sq(SqList& L)         //引用&符号的作用：形参变化，改变实参    
{
    L.elem = new Book[MAXSIZE];      //动态分配存储空间
    if (!L.elem)exit(OVERFLOW);     //分配空间失败，程序结束            
    L.length = 0;                    //初始化表长为0
    return OK;
}
int Input_Sq(SqList& L)            //引用&符号的作用：形参变化，改变实参
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        cin >> L.elem[i].no >> L.elem[i].name >> L.elem[i].price;
        if (L.elem[i].no == "0" && L.elem[i].name == "0" && L.elem[i].price == 0)
            return OK;            //非法输入则函数结束
        else
            L.length++;           //合法输入，表长才+1
    }
}
int Sort_Sq(SqList L)             //冒泡降序排序
{
    Book b;                       //交换桥梁
    for (int i = 0; i < L.length - 1; i++)
        for (int j = 0; j < L.length - i - 1; j++)
            if (L.elem[j].price < L.elem[j + 1].price)
            {
                b = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = b;
            }
    return OK;
}
int Output_Sq(SqList L)
{
    for (int i = 0; i < L.length; i++)
        cout << L.elem[i].no << " " << L.elem[i].name << " " << fixed << setprecision(2) << L.elem[i].price << endl;
    return OK;
}
int main()
{
    SqList L;            //定义一个SqList的顺序表L
    InitList_Sq(L);      //创建：分配空间，初始化
    Input_Sq(L);         //输入数据
    Sort_Sq(L);          //降序排序
    Output_Sq(L);        //输出数据
    return 0;
}
