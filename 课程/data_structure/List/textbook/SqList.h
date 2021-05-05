#include <iostream>
using namespace std;

typedef int ElemType;

/* 线性表的顺序存储结构(动态分配) */
#define InitSize 100     // 表长度的初始分配量
#define LISTINCREMENT 10 // 分配增量

typedef struct {
    ElemType *data;      // 存储空间基址
    int MaxSize, length; // 数组的最大容量和当前元素个数(长度)

} SqList; // 顺序表的类型定义(动态分配)

SqList L; // 声明一个顺序表L(它是一个结构体变量)

/* 初始化一个空的顺序表(为顺序表分配存储空间) */
bool InitList(SqList &L)
{
    L.elem = (ElemType *)malloc(InitSize * sizeof(ElemType)); // 分配存储空间
    if (!L.elem) // 存储分配失败
        exit(OVERFLOW);

    L.length = 0;         // 空表长度为0
    L.MaxSize = InitSize; // 初始存储容量
    return true;
}

/* 插入操作，在表L中第x个位置之前插入新的数据元素e */
bool ListInsert(SqList &L, int x, ElemType e)
{
    if (x<1 || x>L.length + 1) // 插入的位置非法
        return false;

    ElemType *newbase, *p, *q; // newbase存放新的基地址，p和q为辅助指针 
    if (L.length == L.MaxSize) //当前存储空间已满，增加分配
    {
        newbase = (ElemType *)realloc(L.elem, (L.MaxSize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);         // 存储分配失败
        L.elem = newbase;           // 新基址
        L.MaxSize += LISTINCREMENT; // 增加存储容量
    }
    q = &(L.data[x - 1]); // q为插入位置
    for (p = &(L.data[L.length - 1]); p >= q; p--) // 插入位置及之后的元素右移
    {
        *(p + 1) = *p;
    }
    *q = e;     // 在插入位置 q 插入新的元素e
    L.length++; // 表长加1
    return true;
}

/* 删除操作，删除表L中第x个位置的元素，并用e返回删除元素的值 */
bool ListDelete(SqList &L, int x, Elemtype &e)
{
    if (x<1 || x>L.length) // 删除的位置非法
        return false;

    ElemType *p, *q; // p和q为辅助指针 

    p = &(L.elem[x - 1]);        // p为被删除元素的位置
    e = *p;                      // 被删除元素的值赋给e
    q = &(L.elem[L.length - 1]); // 表尾元素的位置
    for (p++; p <= q; p++)       // 被删除元素之后的元素左移
    {
        *(p - 1) = *p;
    }
    L.length--; // 表长减1
    return true;
}

/* 按值查找操作，在表L中查找具有给定关键字(e)值的元素 */
int LocateElem(SqList L, ElemType e)
{
    for (int i = 0; i < L.length; i++)
        if (L.data[i] == e)
            return i + 1; // 下标为i的元素值等于e，返回其位序i+1
    return 0;             // 退出循环，说明查找失败(0表示未找到)
}

/* 按位查找操作，找到表L中第i个位置的元素，并用e返回其值 */
bool GetElem(SqList &L, int x, ElemType &e)
{
    if (x<1 || x>L.length)
        return false;
    e = L.elem[x - 1]; // 位序为i的元素，其下标为i-1
    return true;
}