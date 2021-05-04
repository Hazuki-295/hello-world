#pragma once

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

#include <iostream>
using namespace std;

/* 顺序表存储结构 */
typedef struct {
    ElemType *elem; // 存储空间基址
    int length; // 当前长度
    int listsize; // 当前分配的存储容量（以sizeof(ElemType)为单位）
} SqList;

/* 初始化线性表 */
SqList InitList()
{
    SqList L;
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); // 数据域
    if (!L.elem) // 存储分配失败
        exit(1); // OVERFLOW

    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return L;
}

/* 线性表插入操作 */
bool ListInsert(SqList &L, int x, ElemType e)
{
    if (x<1 || x>L.length + 1) // 插入的位置非法(注意："线性表末尾后一个位置"属于合法位置)
        return false;

    ElemType *newbase, *p, *q;
    if (L.length == L.listsize) // 当前存储空间已满，增加分配
    {
        newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(1); // OVERFLOW

        L.elem = newbase; //新基址
        L.listsize += LISTINCREMENT; //增加存储容量
    }
    q = &(L.elem[x - 1]); //q为插入位置
    for (p = &(L.elem[L.length - 1]); p >= q; p--) //插入位置及之后的元素右移
    {
        *(p + 1) = *p;
    }
    *q = e; //在插入的位置q插入新的元素e
    L.length++;
    return true;
}

/* 线性表删除操作 */
bool ListDelete(SqList &L, int x)
{
    ElemType *p, *q;
    if (x<1 || x>L.length)
        return false;

    p = &(L.elem[x - 1]); //p为被删除元素的位置
    q = &(L.elem[L.length - 1]); //表尾元素的位置
    for (++p; p <= q; p++) //被删除元素之后的元素左移
    {
        *(p - 1) = *p;
    }
    L.length--;
    return true;
}

/* 按位查找 */
bool GetElem(SqList &L, int x)
{
    if (x<1 || x>L.length)
        return false;

    cout << L.elem[x - 1] << endl;
    return true;
}

/* 按值查找 */
int LocateElem(SqList &L, ElemType e) {
    for (int i = 0; i < L.length; i++)
        if (L.elem[i] == e)
            return i + 1; //下标为i的元素值等于e，返回其位序i+1
    return 0; //退出循环，说明查找失败
}

/* 输出操作 */
bool PrintList(SqList L)
{
    for (int i = 1; i <= L.length; i++)
    {
        cout << L.elem[i - 1] << endl;
    }
    return true;
}