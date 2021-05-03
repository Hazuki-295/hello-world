#pragma once

#define MAXSIZE 50

typedef int ElemType;

#include <iostream>
using namespace std;

/* 栈的顺序存储类型 */
typedef struct {
    ElemType data[MAXSIZE];  // 存放栈中元素
    int top;                 // 栈顶指针
} SqStack;

SqStack S;

/*
* 栈顶下标：S.top，初始时设置 S.top = -1
* 栈顶元素：S.data[S.top]
* 进栈操作：栈不满时，栈顶指针先加1，再送值到栈顶元素
* 出栈操作：栈非空时，先取栈顶元素值，再将栈顶指针减1
* 栈空条件：S.top = -1
* 栈满条件：S.top = MAXSIZE - 1
* 栈长：S.top + 1
*/



/* 初始化 */
void InitStack(SqStack &S) 
{
    S.top = -1; // 初始化栈顶指针
}

/* 判栈空 */
bool StackEmpty(SqStack S) 
{
    if (S.top == -1)  // 栈空
        return true;
    else              // 栈不空
        return false;
}

/* 进栈 */
bool Push(SqStack &S, ElemType x) 
{
    if (S.top == MAXSIZE - 1)  // 栈满，报错
        return false;
    S.data[++S.top] = x;       // 指针先加1，再入栈
    return true;
}


/* 出栈 */
bool Pop(SqStack &S, ElemType &x) 
{
    if (S.top == -1)     // 栈空，报错
        return false;
    x = S.data[S.top--]; // 先出栈，指针再减1
    return true;
}

/* 读栈顶元素 */
bool GetTop(SqStack S, ElemType &x) 
{
    if (S.top == -1)     // 栈空，报错
        return false;
    x = S.data[S.top];   // x记录栈顶元素
    return true;
}
