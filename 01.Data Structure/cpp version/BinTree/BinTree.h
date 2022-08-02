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
    ~BinTree() { if (_size > 0) remove(_root); } // 析构函数
    /* 访问内部成员接口 */
    int size() const { return _size; } // 规模
    bool empty() const { return !_root; } // 判空
    BinNodePosi<T> root() const { return _root; } // 树根
    /* 操作接口 */
    BinNodePosi<T> insertAsRoot(T const &e); // 插入根节点
    BinNodePosi<T> insertAsLC(BinNodePosi<T> x, T const &e); // 将e作为x的左孩子（原无）插入
    BinNodePosi<T> insertAsRC(BinNodePosi<T> x, T const &e); // 将e作为x的右孩子（原无）插入
    BinNodePosi<T> attachAsLC(BinNodePosi<T> x, BinTree<T> *&subTree); // 将子树S作为x的左子树（原无）接入
    BinNodePosi<T> attachAsRC(BinNodePosi<T> x, BinTree<T> *&subTree); // 将子树S作为x的右子树（原无）接入
    int remove(BinNodePosi<T> x); // 子树删除
    BinTree<T> *secede(BinNodePosi<T> x); // 子树分离
}; // BinTree

/* 二叉树节点的高度更新：一旦有节点加入或离开二叉树，则更新其所有祖先的高度。 */
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

/* 二叉树节点的插入：将e创建为新节点，作为根节点或孩子节点插入树中。 */
template<typename T>
BinNodePosi<T> BinTree<T>::insertAsRoot(T const &e) { // 将e当作根节点插入空的二叉树
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T> // x祖先的高度可能增加，其余节点必然不变
BinNodePosi<T> BinTree<T>::insertAsLC(BinNodePosi<T> x, T const &e) { // assert: 插入之前，节点x尚无左孩子
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>
BinNodePosi<T> BinTree<T>::insertAsRC(BinNodePosi<T> x, T const &e) { // 与 insertAsLC() 完全对称
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

/* 二叉树子树接入：将S当作节点x的子树接入，S本身置空。 */
template<typename T>
BinNodePosi<T> BinTree<T>::attachAsLC(BinNodePosi<T> x, BinTree<T> *&subTree) { // assert: 接入之前，节点x尚无左子树
    if ((x->lc = subTree->_root)) { // 接入的不是空树
        x->lc->parent = x; // 更新子树根节点的父节点指针，完成接入

        _size += subTree->_size; // 更新全树规模与x所有祖先的高度
        updateHeightAbove(x);

        subTree->_root = nullptr; // 置空原子树
        subTree->_size = 0;
    }
    delete subTree;    // 释放原树，并将
    subTree = nullptr; // 传入的指针置空，防止引用野指针
    return x; // 返回接入位置
}

template<typename T>
BinNodePosi<T> BinTree<T>::attachAsRC(BinNodePosi<T> x, BinTree<T> *&subTree) { // 与 attachAsLC() 完全对称
    if ((x->rc = subTree->_root)) {
        x->rc->parent = x;
        _size += subTree->_size;
        updateHeightAbove(x);
        subTree->_root = nullptr;
        subTree->_size = 0;
    }
    delete subTree;
    subTree = nullptr;
    return x;
}

/* 二叉树子树删除：删除二叉树中以位置x处节点为根的子树，返回该树原先的规模。 */
template<typename T>
int BinTree<T>::remove(BinNodePosi<T> x) { // assert: x为二叉树中的合法位置
    if (x != _root) {
        FromParentTo(*x) = nullptr; // 切断来自父节点的指针
        updateHeightAbove(x->parent); // 更新祖先高度（其余节点亦不变）
    }
    int n = removeAt(x); // 删除子树（递归地删除子树中的所有节点）
    _size -= n; // 更新规模
    return n; // 返回删除节点总数
}

template<typename T>
static int removeAt(BinNodePosi<T> x) {
    if (!x) return 0; // 递归基，空树
    int n = 1 + removeAt(x->lc) + removeAt(x->rc); // 递归释放左、右子树
    delete x; // 释放被摘除节点
    return n; // 返回删除节点总数
}

/* 二叉树子树分离：将子树x从当前树中摘除，将其封装为一颗独立子树返回。 */
template<typename T>
BinTree<T> *BinTree<T>::secede(BinNodePosi<T> x) { // assert: x为二叉树中的合法位置
    if (x != _root) {
        FromParentTo(*x) = nullptr; // 切断来自父节点的指针
        updateHeightAbove(x->parent); // 更新原树中所有祖先的高度
    }
    /* 以上与 BinTree<T>::remove() 一致；以下还需对分离出来的子树重新封装。 */
    BinTree<T> *subTree = new BinTree<T>; // 创建空树
    subTree->_root = x;  // 新树以x为树根，并
    x->parent = nullptr; // 从原树中断开
    subTree->_size = x->size(); // 计算子树规模并更新

    _size -= subTree->_size; // 更新原树规模
    return subTree; // 返回封装后的子树
}