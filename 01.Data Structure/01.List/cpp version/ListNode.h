#pragma once

using Rank = int; // 秩

template<typename T> struct ListNode;
template<typename T> using ListNodePosi = ListNode<T> *; // 列表节点位置

template<typename T> struct ListNode { // 列表节点模板类（以双向链表形式实现）
// 成员
    T data; // 数据域
    ListNodePosi<T> pred; // 前驱节点
    ListNodePosi<T> succ; // 后继节点
// 构造函数
    ListNode() {} // （默认构造函数）针对header和trailer的构造
    ListNode(T e, ListNodePosi<T> p = nullptr, ListNodePosi<T> s = nullptr)
            : data(e), pred(p), succ(s) {} // 一般节点的默认构造器
// 操作接口
    ListNodePosi<T> insertAsPred(T const &e); // 作为当前节点直接前驱插入新节点
    ListNodePosi<T> insertAsSucc(T const &e); // 作为当前节点直接后继插入新节点
};

/* 将e作为当前节点的直接前驱，插入当前节点所属的列表（设有哨兵头节点header） */
template<typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(T const &e) {
    ListNodePosi<T> x = new ListNode(e, pred, this); // 创建新节点
    pred->succ = x; // 1.使new成为当前节点前驱节点的后继
    pred = x;       // 2.使new成为当前节点的前驱（设置正向链接，次序不能颠倒）
    return x; // 返回新节点的位置
}

/* 将e作为当前节点的直接后继，插入当前节点所属的列表（设有哨兵尾节点trailer） */
template<typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const &e) {
    ListNodePosi<T> x = new ListNode(e, this, succ); // 创建新节点
    succ->pred = x; // 1.使new成为当前节点后继节点的前驱
    succ = x;       // 2.使new成为当前节点的后继（设置逆向链接，次序不能颠倒）
    return x; // 返回新节点的位置
}