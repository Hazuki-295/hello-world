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

/* 入栈：若栈S未满，则将e插至栈顶，成为新的栈顶。 */
void Push(SqStack &S, ElemType e) {
    if (S.top == S.MaxSize - 1) { // 当前存储空间已满，扩容
        ElemType *p = S.data;
        S.data = new ElemType[S.MaxSize <<= 1]; // 容量加倍
        for (int i = 0; i < S.top + 1; i++) {   // 将数据复制到新区域
            S.data[i] = p[i];
        }
        delete[] p;
    }
    S.data[++S.top] = e; // 栈顶指针先加1，再送值到栈顶
}

/* 出栈：若栈S非空，则弹出栈顶元素，并返回其值。 */
ElemType Pop(SqStack &S) {
    return S.data[S.top--]; // 先取栈顶元素的值，再将栈顶指针减1
}

/* 读栈顶元素：若栈S非空，则返回栈顶元素的引用。 */
ElemType &GetTop(SqStack S) {
    return S.data[S.top]; // 返回栈顶元素的引用
}