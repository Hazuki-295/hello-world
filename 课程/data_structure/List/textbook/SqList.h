#pragma once

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

#include <iostream>
using namespace std;

/* ˳���洢�ṹ */
typedef struct {
    ElemType *elem; // �洢�ռ��ַ
    int length; // ��ǰ����
    int listsize; // ��ǰ����Ĵ洢��������sizeof(ElemType)Ϊ��λ��
} SqList;

/* ��ʼ�����Ա� */
SqList InitList()
{
    SqList L;
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); // ������
    if (!L.elem) // �洢����ʧ��
        exit(1); // OVERFLOW

    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return L;
}

/* ���Ա������� */
bool ListInsert(SqList &L, int x, ElemType e)
{
    if (x<1 || x>L.length + 1) // �����λ�÷Ƿ�(ע�⣺"���Ա�ĩβ��һ��λ��"���ںϷ�λ��)
        return false;

    ElemType *newbase, *p, *q;
    if (L.length == L.listsize) // ��ǰ�洢�ռ����������ӷ���
    {
        newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(1); // OVERFLOW

        L.elem = newbase; //�»�ַ
        L.listsize += LISTINCREMENT; //���Ӵ洢����
    }
    q = &(L.elem[x - 1]); //qΪ����λ��
    for (p = &(L.elem[L.length - 1]); p >= q; p--) //����λ�ü�֮���Ԫ������
    {
        *(p + 1) = *p;
    }
    *q = e; //�ڲ����λ��q�����µ�Ԫ��e
    L.length++;
    return true;
}

/* ���Ա�ɾ������ */
bool ListDelete(SqList &L, int x)
{
    ElemType *p, *q;
    if (x<1 || x>L.length)
        return false;

    p = &(L.elem[x - 1]); //pΪ��ɾ��Ԫ�ص�λ��
    q = &(L.elem[L.length - 1]); //��βԪ�ص�λ��
    for (++p; p <= q; p++) //��ɾ��Ԫ��֮���Ԫ������
    {
        *(p - 1) = *p;
    }
    L.length--;
    return true;
}

/* ��λ���� */
bool GetElem(SqList &L, int x)
{
    if (x<1 || x>L.length)
        return false;

    cout << L.elem[x - 1] << endl;
    return true;
}

/* ��ֵ���� */
int LocateElem(SqList &L, ElemType e) {
    for (int i = 0; i < L.length; i++)
        if (L.elem[i] == e)
            return i + 1; //�±�Ϊi��Ԫ��ֵ����e��������λ��i+1
    return 0; //�˳�ѭ����˵������ʧ��
}

/* ������� */
bool PrintList(SqList L)
{
    for (int i = 1; i <= L.length; i++)
    {
        cout << L.elem[i - 1] << endl;
    }
    return true;
}