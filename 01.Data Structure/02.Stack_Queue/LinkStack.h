#pragma once

#include "../01.List/LinkList.h"

/* 栈的链式表示（以单链表形式实现，仅在头部进行插入和删除） */
typedef struct {
    ListNode *head; // 头结点指针
} LinkStack; // 链栈的类型定义

/* 初始化栈。构造一个空栈。 */
void InitStack(LinkStack &S) {
    S.head = new ListNode;  // 创建头结点
    S.head->next = nullptr; // 初始为空栈，无数据结点
}

/* 销毁操作。销毁栈，并释放栈S所占用的内存空间。 */
void DestroyStack(LinkStack &S) {
    DestroyList(S.head); // 链栈由单链表实现，析构操作相同
}

/* 判空操作。若S为空栈，则返回true，否则返回false。 */
bool StackEmpty(LinkStack S) {
    return S.head->next == nullptr;
}

/* 入栈：若栈S未满，则将e插至栈顶，成为新的栈顶。 */
void Push(LinkStack &S, ElemType e) {
    ListNode *x = new ListNode(e, S.head->next); // 创建新结点，指针域指向当前栈顶结点
    S.head->next = x; // 在链表的头部插入，成为新的栈顶
}

/* 出栈：若栈S非空，则弹出栈顶元素，并返回其值。 */
ElemType Pop(LinkStack &S) {
    ListNode *p = S.head->next; // 出栈结点
    ElemType e = p->data;       // 备份出栈元素的值
    S.head->next = p->next; // 将出栈结点从链中断开
    delete p; // 释放出栈结点
    return e;
}

/* 读栈顶元素：若栈S非空，则返回栈顶元素的引用。 */
ElemType &GetTop(LinkStack S) {
    ListNode *p = S.head->next; // 栈顶结点
    return p->data; // 返回栈顶元素的引用
}