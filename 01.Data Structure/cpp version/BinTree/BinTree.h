#pragma once

#include <iostream> // 引入max()

using namespace std;

#include "BinNode.h" // 引入二叉树节点类

template<typename T> class BinTree { // 二叉树模板类
protected:
    int _size; // 规模
    BinNodePosi<T> _root; // 根节点
    virtual int updateHeight(BinNodePosi<T> x); // 更新节点x的高度（派生类必要时重写）
    void updateHeightAbove(BinNodePosi<T> x); // 自下而上，更新节点x及其祖先的高度

public:
    BinTree() : _size(0), _root(nullptr) {} // 默认构造函数，构造一颗空树
    /* 访问内部成员接口 */
    int size() const { return _size; } // 规模
    bool empty() const { return !_root; } // 判空
    BinNodePosi<T> root() const { return _root; } // 树根
    /* 操作接口 */
    BinNodePosi<T> insertAsRoot(T const &e); // 插入根节点
    BinNodePosi<T> insertAsLC(BinNodePosi<T> x, T const &e); // 将e作为x的左孩子（原无）插入
    BinNodePosi<T> insertAsRC(BinNodePosi<T> x, T const &e); // 将e作为x的右孩子（原无）插入
}; // BinTree

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi<T> x) { // 更新节点x的高度
    return x->height = 1 + max(stature(x->lc), stature(x->rc)); // 具体规则因树不同而异
} // O(1)

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi<T> x) { // 更新节点x及其祖先的高度
    while (x) { // 从x出发，向上更新历代祖先
        updateHeight(x);
        x = x->parent;
    } // 可优化，一旦高度未变即可终止
} // O( n = depth(x) )

template<typename T>
BinNodePosi<T> BinTree<T>::insertAsRoot(T const &e) { // 将e当作根节点插入空的二叉树
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>
BinNodePosi<T> BinTree<T>::insertAsLC(BinNodePosi<T> x, T const &e) { // assert: 插入之前，节点x尚无左孩子
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x); // x祖先的高度可能增加，其余节点必然不变
    return x->lc;
}

template<typename T>
BinNodePosi<T> BinTree<T>::insertAsRC(BinNodePosi<T> x, T const &e) { // 与 insertAsLC() 完全对称
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}