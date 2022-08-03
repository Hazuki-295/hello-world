#pragma once

#include "../Stack_Queue/Queue.h" // 引入队列和栈
#include "../Stack_Queue/Stack.h"

#include "BinNode_macro.h" // 二叉树节点的状态与性质

#define stature(p) ((p) ? (p)->height : -1) // 节点高度，与“空树高度为-1”的约定相统一

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
// 遍历
    /* 递归式遍历 */
    template<typename VST> void travPre(VST &visit) { travPre_R(this, visit); }   // 子树先序遍历
    template<typename VST> void travIn(VST &visit) { travIn_R(this, visit); }     // 子树中序遍历
    template<typename VST> void travPost(VST &visit) { travPost_R(this, visit); } // 子树后序遍历
    /* 迭代式遍历 */
    template<typename VST> void travLevel(VST &visit); // 子树层次遍历
    template<typename VST> void travPre_I(VST &visit) { travPre_Iteration(this, visit); } // 子树先序遍历
    template<typename VST> void travIn_I(VST &visit) { travIn_Iteration(this, visit); }   // 子树中序遍历
};

/* 子树规模：后代总数，亦即以其为根的子树的规模。 */
template<typename T> int BinNode<T>::size() {
    int s = 1; // 计入本身
    if (lc) s += lc->size(); // 递归，计入左子树规模
    if (rc) s += rc->size(); // 递归，计入右子树规模
    return s;
} // O(n = |size|)

/* 二叉树节点的插入：将e作为当前节点的孩子节点插入。 */
template<typename T> BinNodePosi<T> BinNode<T>::insertAsLC(T const &e) { // assert: 插入之前，当前节点尚无左孩子
    return lc = new BinNode(e, this); // 将e作为当前节点的左孩子插入二叉树
}

template<typename T> BinNodePosi<T> BinNode<T>::insertAsRC(T const &e) { // assert: 插入之前，当前节点尚无右孩子
    return rc = new BinNode(e, this); // 将e作为当前节点的右孩子插入二叉树
}

/* 二叉树的遍历：按照某种约定的次序，对子树中的节点各访问一次且仅一次。 */
template<typename T, typename VST>
void travPre_R(BinNodePosi<T> x, VST &visit) { // 二叉树先序遍历算法（递归版）
    if (!x) return; // 递归基，空树直接返回
    visit(x->data); // 访问根节点
    travPre_R(x->lc, visit); // 递归，先序遍历左子树
    travPre_R(x->rc, visit); // 递归，先序遍历右子树
}

template<typename T, typename VST>
void travIn_R(BinNodePosi<T> x, VST &visit) { // 二叉树中序遍历算法（递归版）
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template<typename T, typename VST>
void travPost_R(BinNodePosi<T> x, VST &visit) { // 二叉树后序遍历算法（递归版）
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

// 迭代式遍历算法：层次遍历，以及将二叉树的递归式遍历算法，改写为对应的迭代版本。
template<typename T> template<typename VST>
void BinNode<T>::travLevel(VST &visit) { // 二叉树层次遍历算法
    Queue<BinNodePosi<T>> Q; // 辅助队列
    Q.enqueue(this); // 根节点入队
    while (!Q.empty()) { // 在队列再次变空之前，反复迭代
        BinNodePosi<T> x = Q.dequeue(); // 取出队首节点，并
        visit(x->data); // 访问之
        if (HasLChild(*x)) Q.enqueue(x->lc); // 左孩子入队
        if (HasRChild(*x)) Q.enqueue(x->rc); // 右孩子入队
    }
}

/* 藤缠树：从当前节点出发，沿左侧藤不断深入，自顶向下访问藤上节点，直至遇到没有左分支的节点。 */
template<typename T, typename VST>
static void visitAlongVine(BinNodePosi<T> x, VST &visit, Stack<BinNodePosi<T>> &S) {
    while (x) { // 反复地
        visit(x->data); // 访问当前节点
        if (HasRChild(*x)) S.push(x->rc); // 右子树（根）入栈暂存（将来逆序出栈）
        x = x->lc; // 沿藤下行
    }
}

template<typename T, typename VST>
void travPre_Iteration(BinNodePosi<T> x, VST &visit) { // 二叉树先序遍历算法（迭代版）
    Stack<BinNodePosi<T>> S; // 辅助栈
    while (true) { // 以右子树（及全树根）为单位，逐批访问节点
        visitAlongVine(x, visit, S); // 访问子树x的左侧藤，沿途各节点的右子树（根）入栈缓冲
        if (S.empty()) break; // 栈空则遍历结束，退出
        x = S.pop(); // 弹出下一右子树（根）
    }
}

/* 藤缠树：从当前节点出发，沿左侧藤不断深入，将沿途各节点入栈，逆序保存，直至没有左孩子的末端节点。 */
template<typename T>
static void goAlongVine(BinNodePosi<T> x, Stack<BinNodePosi<T>> &S) {
    while (x) {
        S.push(x); // 逐层深入，沿藤蔓各节点依次入栈（将来逆序出栈，宏观上的拼接次序）
        x = x->lc;
    }
}

template<typename T, typename VST>
void travIn_Iteration(BinNodePosi<T> x, VST &visit) { // 二叉树中序遍历算法（迭代版）
    Stack<BinNodePosi<T>> S; // 辅助栈
    while (true) {
        goAlongVine(x, S); // 从当前节点出发，左侧藤上节点逐批入栈
        if (S.empty()) break; // 直至所有节点处理完毕
        x = S.pop();    // 栈顶节点x的左子树或为空，或已遍历（等效于空），故可以
        visit(x->data); // 立即访问之，再
        x = x->rc;      // 转向其右子树（可能为空）
    } // 每个节点出栈时，其左子树或不存在，或已完成遍历，而右子树尚未入栈。于是，每当有节点出栈，只需访问它，然后从其右孩子出发...
}