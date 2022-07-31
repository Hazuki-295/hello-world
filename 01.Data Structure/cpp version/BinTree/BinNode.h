#pragma once

template<typename T> struct BinNode;
template<typename T> using BinNodePosi = BinNode<T> *; // 二叉树节点位置

template<typename T> struct BinNode { // 二叉树节点模板类
// 成员
    T data; // 数据域
    BinNodePosi<T> parent; // 父节点
    BinNodePosi<T> lc, rc; // 左、右孩子
// 节点状态信息
    int height; // 节点的高度，子树高度
    int size(); // 子树规模。统计当前节点后代总数，亦即以其为根的子树的规模
// 构造函数
    BinNode() : parent(nullptr), lc(nullptr), rc(nullptr), height(0) {} // 默认构造函数
    BinNode(T e, BinNodePosi<T> p = nullptr, BinNodePosi<T> lc = nullptr, BinNodePosi<T> rc = nullptr, int h = 0)
            : data(e), parent(p), lc(lc), rc(rc), height(h) {} // 指定数据域（及父节点）的构造函数
// 操作接口
    BinNodePosi<T> insertAsLC(T const &e); // 作为当前节点的左孩子插入新节点
    BinNodePosi<T> insertAsRC(T const &e); // 作为当前节点的右孩子插入新节点
};

/* 子树规模：后代总数，亦即以其为根的子树的规模。 */
template<typename T> int BinNode<T>::size() {
    int s = 1; // 计入本身
    if (lc) s += lc->size(); // 递归，计入左子树规模
    if (rc) s += rc->size(); // 递归，计入右子树规模
    return s;
} // O(n = |size|)

template<typename T> BinNodePosi<T> BinNode<T>::insertAsLC(T const &e) { // assert: 插入之前，当前节点尚无左孩子
    return lc = new BinNode(e, this); // 将e作为当前节点的左孩子插入二叉树
}

template<typename T> BinNodePosi<T> BinNode<T>::insertAsRC(T const &e) { // assert: 插入之前，当前节点尚无右孩子
    return rc = new BinNode(e, this); // 将e作为当前节点的右孩子插入二叉树
}