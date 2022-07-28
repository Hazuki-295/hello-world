#pragma once

#include <iostream>

using namespace std;

typedef int ElemType;

/* 线性表的链式表示（单链表） */
typedef struct ListNode {
// 成员
    ElemType data;  // 数据域
    ListNode *next; // 指针域
// 构造函数
    ListNode() {} // （默认构造函数）针对头结点的构造
    ListNode(ElemType e, ListNode *p = nullptr) : data(e), next(p) {} // 一般节点的默认构造器
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

/* 求表长。返回线性表L的长度，即L中数据元素的个数。 */
int Length(LinkList L) {
    ListNode *p = L; // 从头结点出发
    int length = 0;  // 顺着指针链计数
    while ((p = p->next) != nullptr) {
        length++;
    }
    return length;
}

/* 判空操作。若L为空表，则返回true，否则返回false。 */
bool Empty(LinkList L) {
    return L->next == nullptr;
}

/* 按值查找操作。在表L中查找具有给定关键字值的结点，并返回指向该结点的指针。 */
ListNode *LocateElem(LinkList L, ElemType e) {
    ListNode *p = L; // 从头结点出发
    while ((p = p->next) != nullptr && p->data != e); // 找到具有给定关键字值的结点
    return p; // 查找成功返回指向该结点的指针，失败返回nullptr
}

/* 按位查找：找到表L中第i个位置的结点，并返回指向该结点的指针。 */
ListNode *GetElem(LinkList L, int i) {
    if (i < 0) return nullptr;
    ListNode *p = L; // 从头结点出发
    int index = 0;   // 当前p指向的结点的位序（头结点的位序视为0）
    while (p != nullptr && index < i) { // 顺着指针域找到第i个结点
        p = p->next;
        index++;
    }
    return p; // 返回指向该结点的指针；若i越界将返回nullptr，若i=0将返回头结点
} // O(n)

/* 指定结点的后插操作：将e作为p的直接后继插入。 */
bool InsertAfter(ListNode *p, ElemType e) {
    if (p == nullptr) return false;
    ListNode *x = new ListNode(e, p->next); // 创建新结点，以当前结点p的后继作为新结点的后继
    p->next = x; // 使new成为当前节点的后继
    return true;
} // O(1)

/* 指定结点的前插操作：将e作为p的直接前驱插入。 */
bool InsertBefore(ListNode *p, ElemType e) {
    if (p == nullptr) return false;
    ListNode *x = new ListNode(p->data, p->next); // 创建新结点，链接到p后，并拷贝p的值
    p->next = x; // 使new成为当前节点的后继
    p->data = e; // 更新当前结点的数据域，等效的前插操作
    return true;
} // O(1)

/* 插入操作。在表L中的第i个位置上插入指定元素e。 */
bool ListInsert(LinkList &L, int i, ElemType e) {
    ListNode *p = GetElem(L, i - 1); // 找到插入位置的前驱结点，并
    return InsertAfter(p, e); // 将新结点作为其直接后继插入
} // O(n)

/* 删除操作。删除表L中第i个位置上的元素，并用e返回删除元素的值。 */
bool ListDelete(LinkList &L, int i, ElemType &e) {
    ListNode *p = GetElem(L, i - 1);        // 找到删除位置的前驱结点
    if (p == nullptr || p->next == nullptr) { // 删除位置非法，或被删除结点不存在(试图删除尾哨兵)
        return false;
    }
    ListNode *q = p->next;   // 备份待删除结点q
    p->next = p->next->next; // 将q结点从链中断开
    e = q->data; // 用e返回元素的值
    delete q;    // 释放结点
    return true;
} // O(n)

/* 头插法：从空表开始，每次将新结点作为首元素插入，逆向建立单链表。 */
void List_HeadInsert(LinkList &L, int n) {
    if (L != nullptr && L->next != nullptr) { // 释放原有数据
        DestroyList(L);
        InitList(L);
    }
    ElemType temp;
    while (n-- > 0) { // 依次在表头插入n个新结点
        cin >> temp;
        ListNode *s = new ListNode(temp, L->next); // 创建新结点s
        L->next = s; // s成为新的表头结点
    }
}

/* 尾插法：从空表开始，每次将新结点作为末元素插入，正向建立单链表。 */
void List_TailInsert(LinkList &L, int n) {
    if (L != nullptr && L->next != nullptr) { // 释放原有数据
        DestroyList(L);
        InitList(L);
    }
    ElemType temp;
    ListNode *rail = L; // 表尾指针，初始指向头节点
    while (n-- > 0) {   // 依次在表尾插入n个新结点
        cin >> temp;
        ListNode *s = new ListNode(temp, nullptr); // 创建新结点s
        rail->next = s; // s成为新的表尾结点
        rail = s;       // 更新表尾指针
    }
}

/* 输出操作。按前后顺序输出线性表L的所有元素的值。 */
void PrintList(LinkList L) {
    cout << '[';
    ListNode *p = L;
    while ((p = p->next) != nullptr) {
        cout << p->data;
        if (p->next != nullptr) cout << ", ";
    }
    cout << ']';
}