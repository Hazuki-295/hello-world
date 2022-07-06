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
    ListNodePosi<T> insertAsPred(T const &e); // 作为当前节点前驱插入新节点
    ListNodePosi<T> insertAsSucc(T const &e); // 作为当前节点后继插入新节点
};