#pragma once

typedef int ElemType;

/* 栈的顺序表示（顺序栈） */
#define InitSize 10
typedef struct {
    ElemType *data; // 栈中的元素，动态分配
    int MaxSize;    // 栈的最大容量
    int top;        // 栈顶指针，指向当前栈顶元素
} SqStack;          // 顺序栈的类型定义

/* 初始化栈。构造一个空栈。 */
void InitStack(SqStack &S) {
    S.data = new ElemType[S.MaxSize = InitSize];
    S.top = -1; // 初始化栈顶指针
}

/* 销毁操作。销毁栈，并释放栈S所占用的内存空间。 */
void DestroyStack(SqStack &S) {
    delete[] S.data;
}

/* 判空操作。若S为空栈，则返回true，否则返回false。 */
bool StackEmpty(SqStack S) {
    return S.top == -1;
}