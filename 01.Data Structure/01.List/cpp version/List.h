#pragma once

#include "ListNode.h" // 引入列表节点类

template<typename T> class List { // 列表模板类
private:
    int _size; // 规模，当前实际节点的数量（不包括头、尾哨兵）
    ListNodePosi<T> header;  // 头哨兵
    ListNodePosi<T> trailer; // 尾哨兵

protected:
    void init(); // 列表创建时的初始化

public:
// 构造函数
    List() { init(); } // 默认构造函数
    /* 基于复制的构造函数 */
    List(List<T> const &L); // 拷贝构造函数，整体复制列表L
    List(List<T> const &L, Rank r, int n); // 复制列表L中自第r项起的n项
    List(ListNodePosi<T> p, int n); // 复制列表中自位置p起的n项
// 析构函数
    ~List(); // 释放（包括头、尾哨兵在内的）所有节点
};

/* 列表初始化，在创建列表对象时统一调用。 */
template<typename T>
void List<T>::init() {
    header = new ListNode<T>;  // 创建头哨兵节点
    trailer = new ListNode<T>; // 创建尾哨兵节点

    header->succ = trailer; // 互联，头哨兵始终无前驱
    header->pred = nullptr;
    trailer->pred = header; // 互联，尾哨兵始终无后继
    trailer->succ = nullptr;

    _size = 0; // 初始规模为0
}