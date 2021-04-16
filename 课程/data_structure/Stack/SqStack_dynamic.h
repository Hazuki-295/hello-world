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

/* 栈的顺序存储表示(动态大小) */
typedef struct {
    ElemType *base; //基地址
    ElemType *top;  //栈底指针
    int stacksize;  //当前已分配的存储空间(以元素为单位)
} SqStack;

SqStack S;

/*
* 栈顶指针：S.top - 1
* 栈顶元素：*(S.top - 1)
* 进栈操作：栈满时，扩容。栈不满时，先赋值，指针再加1。
* 出栈操作：栈非空时，指针先减1，再取值给x
* 栈空条件：S.top == S.base
* 栈满条件：S.top - S.base == S.stacksize
* 栈长：S.top - S.base (元素个数)
*/

/* 构造一个空栈 */
bool InitStack(SqStack &S) {
    
    S.base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!S.base)    //存储分配失败
        return false;

    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return true;

}

/* 进栈操作 */
bool Push(SqStack &S, ElemType x) 
{
    if (S.top - S.base == S.stacksize) { // 栈满，扩容
        S.base = (ElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(ElemType));
        if (!S.base)
            false;

        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }

    *(S.top++) = x;  //与前一种方法不同，先进栈，指针再加1（栈顶指针始终指向栈顶元素的下一个位置）
    return true;

}

/* 出栈操作 */
bool Pop(SqStack &S, ElemType &x) 
{
    if (S.top == S.base) // 栈空，报错
        return false;
    x = *(--S.top);     // 指针先减1，再取值给x
    return true;
}