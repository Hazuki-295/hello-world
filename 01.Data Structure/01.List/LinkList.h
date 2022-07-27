#include <iostream>

typedef int ElemType;

/* 线性表的链式表示（单链表） */
typedef struct ListNode {
// 成员
    ElemType data;     // 数据域
    ListNode *next;    // 指针域
// 构造函数
    ListNode() {} // （默认构造函数）针对头结点的构造
    ListNode(ElemType e, ListNode *p = nullptr)
            : data(e), next(p) {} // 一般节点的默认构造器
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
    ListNode *x = new ListNode(e, p->next); // 创建新结点，以当前结点p的后继为新结点的后继
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
    ListNode *p = GetElem(L, i - 1);
    return InsertAfter(p, e);
} // O(n)