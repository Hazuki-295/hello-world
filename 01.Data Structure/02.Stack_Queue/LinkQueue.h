#pragma once

#include "../01.List/LinkList.h"

/* 队列的链式表示（以带尾结点指针的单链表实现） */
typedef struct {
    ListNode *front; // 队头指针，指向头结点
    ListNode *rear;  // 队尾指针，指向队尾结点
} LinkQueue; // 链队列的类型定义

/* 初始化队列。构造一个空队列。 */
void InitQueue(LinkQueue &Q) {
    Q.front = new ListNode;  // 创建头结点
    Q.front->next = nullptr; // 初始为空队列，无数据结点
    Q.rear = Q.front; // 初始时，使队尾指针也指向头结点
}

/* 销毁操作。销毁队列，并释放队列Q所占用的内存空间。 */
void DestroyQueue(LinkQueue &Q) {
    DestroyList(Q.front); // 链队列由单链表实现，析构操作相同
}

/* 判空操作。若Q为空队列，则返回true，否则返回false。 */
bool QueueEmpty(LinkQueue Q) {
    return Q.front == Q.rear; // 队头、队尾指针均指向头结点为队空
}

/* 入队：若队列Q未满，则将e插至队尾指针所指的位置，成为新的队尾。 */
void Enqueue(LinkQueue &Q, ElemType e) {
    ListNode *x = new ListNode(e, nullptr); // 创建新的队尾节点
    Q.rear->next = x; // 当前队尾结点的指针域，指向新结点
    Q.rear = x; // 更新队尾指针
}

/* 出队：若队列Q非空，删除队头元素，并返回其值。 */
ElemType Dequeue(LinkQueue &Q) {
    ListNode *p = Q.front->next; // 队头结点
    ElemType e = p->data;        // 备份队头元素
    Q.front = p->next; // 将出队结点从链中断开
    if (p == Q.rear) { // 若被删除的是尾结点（亦即，队列中只有一个结点）
        Q.rear = Q.front;; // 更新队尾指针
    }
    delete p; // 释放出队结点
    return e;
}

/* 读队头元素：若队列Q非空，则返回队头元素的引用。 */
ElemType &GetHead(LinkQueue Q) {
    ListNode *p = Q.front->next; // 队头结点
    return p->data; // 返回队头元素的引用
}