/******************************************************************************************
 * Data Structures in C
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2020. All rights reserved.
 ******************************************************************************************/
#pragma once

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int ElemType;

#include <iostream>
using namespace std; 

/* ջ��˳��洢��ʾ(��̬��С) */
typedef struct {
    ElemType *base; //����ַ
    ElemType *top;  //ջ��ָ��
    int stacksize;  //��ǰ�ѷ���Ĵ洢�ռ�(��Ԫ��Ϊ��λ)
} SqStack;

SqStack S;

/*
* ջ��ָ�룺S.top - 1
* ջ��Ԫ�أ�*(S.top - 1)
* ��ջ������ջ��ʱ�����ݡ�ջ����ʱ���ȸ�ֵ��ָ���ټ�1��
* ��ջ������ջ�ǿ�ʱ��ָ���ȼ�1����ȡֵ��x
* ջ��������S.top == S.base
* ջ��������S.top - S.base == S.stacksize
* ջ����S.top - S.base (Ԫ�ظ���)
*/

/* ����һ����ջ */
bool InitStack(SqStack &S) {
    
    S.base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!S.base)    //�洢����ʧ��
        return false;

    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return true;

}

/* ��ջ���� */
bool Push(SqStack &S, ElemType x) 
{
    if (S.top - S.base == S.stacksize) { // ջ��������
        S.base = (ElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(ElemType));
        if (!S.base)
            false;

        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }

    *(S.top++) = x;  //��ǰһ�ַ�����ͬ���Ƚ�ջ��ָ���ټ�1��ջ��ָ��ʼ��ָ��ջ��Ԫ�ص���һ��λ�ã�
    return true;

}

/* ��ջ���� */
bool Pop(SqStack &S, ElemType &x) 
{
    if (S.top == S.base) // ջ�գ�����
        return false;
    x = *(--S.top);     // ָ���ȼ�1����ȡֵ��x
    return true;
}