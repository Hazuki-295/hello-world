#pragma once

#define MAXSIZE 50

typedef int ElemType;

#include <iostream>
using namespace std;

/* ջ��˳��洢���� */
typedef struct {
    ElemType data[MAXSIZE];  // ���ջ��Ԫ��
    int top;                 // ջ��ָ��
} SqStack;

SqStack S;

/*
* ջ���±꣺S.top����ʼʱ���� S.top = -1
* ջ��Ԫ�أ�S.data[S.top]
* ��ջ������ջ����ʱ��ջ��ָ���ȼ�1������ֵ��ջ��Ԫ��
* ��ջ������ջ�ǿ�ʱ����ȡջ��Ԫ��ֵ���ٽ�ջ��ָ���1
* ջ��������S.top = -1
* ջ��������S.top = MAXSIZE - 1
* ջ����S.top + 1
*/



/* ��ʼ�� */
void InitStack(SqStack &S) 
{
    S.top = -1; // ��ʼ��ջ��ָ��
}

/* ��ջ�� */
bool StackEmpty(SqStack S) 
{
    if (S.top == -1)  // ջ��
        return true;
    else              // ջ����
        return false;
}

/* ��ջ */
bool Push(SqStack &S, ElemType x) 
{
    if (S.top == MAXSIZE - 1)  // ջ��������
        return false;
    S.data[++S.top] = x;       // ָ���ȼ�1������ջ
    return true;
}


/* ��ջ */
bool Pop(SqStack &S, ElemType &x) 
{
    if (S.top == -1)     // ջ�գ�����
        return false;
    x = S.data[S.top--]; // �ȳ�ջ��ָ���ټ�1
    return true;
}

/* ��ջ��Ԫ�� */
bool GetTop(SqStack S, ElemType &x) 
{
    if (S.top == -1)     // ջ�գ�����
        return false;
    x = S.data[S.top];   // x��¼ջ��Ԫ��
    return true;
}