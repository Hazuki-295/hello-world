#include <iostream>

typedef int ElemType;

/* 线性表的链式表示（单链表） */
typedef struct ListNode {
    ElemType data;     // 数据域
    ListNode *next;    // 指针域
} ListNode, *LinkList; // 链表结点、链表（头指针）的类型定义

/* 初始化表。构造一个空的线性表。 */
void InitList(LinkList &L) {
    L = new ListNode;  // 创建头结点
    L->next = nullptr; // 初始为空链表，无数据结点
}

/* 销毁操作。销毁线性表，并释放线性表L所占用的内存空间。 */
void DestroyList(LinkList &L) {
    while (L->next != nullptr) {
        ListNode *p = L->next->next; // 备份，防止断链
        delete L->next; // 删除首结点
        L->next = p;    // 新的首结点接替
    }
    delete L; // 删除头结点
}

/* 判空操作。若L为空表，则返回true，否则返回false。 */
bool Empty(LinkList L) {
    return L->next == nullptr;
}