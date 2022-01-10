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
    string no;       	//���    
    string name;	//����
    float price;   	//�۸�
}Book;
typedef struct
{
    Book* elem;        //Book���͵�����ָ��elem
    int length;        //˳���ı�
}SqList;
int InitList_Sq(SqList& L)         //����&���ŵ����ã��βα仯���ı�ʵ��    
{
    L.elem = new Book[MAXSIZE];      //��̬����洢�ռ�
    if (!L.elem)exit(OVERFLOW);     //����ռ�ʧ�ܣ��������            
    L.length = 0;                    //��ʼ����Ϊ0
    return OK;
}
int Input_Sq(SqList& L)            //����&���ŵ����ã��βα仯���ı�ʵ��
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        cin >> L.elem[i].no >> L.elem[i].name >> L.elem[i].price;
        if (L.elem[i].no == "0" && L.elem[i].name == "0" && L.elem[i].price == 0)
            return OK;            //�Ƿ�������������
        else
            L.length++;           //�Ϸ����룬����+1
    }
}
int Sort_Sq(SqList L)             //ð�ݽ�������
{
    Book b;                       //��������
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
    SqList L;            //����һ��SqList��˳���L
    InitList_Sq(L);      //����������ռ䣬��ʼ��
    Input_Sq(L);         //��������
    Sort_Sq(L);          //��������
    Output_Sq(L);        //�������
    return 0;
}
