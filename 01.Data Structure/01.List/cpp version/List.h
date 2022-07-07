#pragma once

#include "ListNode.h" // 引入列表节点类

template<typename T> class List { // 列表模板类
private:
    int _size; // 规模，当前实际节点的数量（不包括头、尾哨兵）
    ListNodePosi<T> header;  // 头哨兵
    ListNodePosi<T> trailer; // 尾哨兵

protected:
    void init(); // 列表创建时的初始化
    void copyNodes(ListNodePosi<T> p, int n); // 复制列表中自位置p起的n项
    int clear(); // 清空所有节点，返回被删除节点的个数

public:
// 构造函数
    List() { init(); } // 默认构造函数
    /* 基于复制的构造函数 */
    List(List<T> const &L) { copyNodes(L.first(), L._size); } // 拷贝构造函数，整体复制列表L
    List(List<T> const &L, Rank r, int n); // 复制列表L中自第r项起的n项
    List(ListNodePosi<T> p, int n) { copyNodes(p, n); } // 复制列表中自位置p起的n项
// 析构函数
    ~List(); // 释放（包括头、尾哨兵在内的）所有节点
// 只读访问接口
    Rank size() const { return _size; }       // 规模
    bool empty() const { return _size <= 0; } // 判空
    ListNodePosi<T> first() const { return header->succ; } // 首节点位置
    ListNodePosi<T> last() const { return trailer->pred; } // 末节点位置
    /* 运算符重载 */
    T &operator[](Rank r) const; // 重载，支持循秩访问（效率低）
    /* 查找接口 */
    bool valid(ListNodePosi<T> p) { return p && trailer != p && header != p; } // 判断位置p是否对外合法（将头、尾节点等同与nullptr）
    ListNodePosi<T> find(T const &e) const { return find(e, _size, trailer); } // 无序列表整体查找
    ListNodePosi<T> find(T const &e, int n, ListNodePosi<T> p) const; // 无序列表区间查找
// 可写访问接口
    /* 插入与删除 */
    ListNodePosi<T> insertAsFirst(T const &e) { return insertAfter(header, e); }  // 将e作为首节点插入
    ListNodePosi<T> insertAsLast(T const &e) { return insertBefore(trailer, e); } // 将e作为末节点插入
    ListNodePosi<T> insertAfter(ListNodePosi<T> p, T const &e);  // 将e作为p的直接后继插入
    ListNodePosi<T> insertBefore(ListNodePosi<T> p, T const &e); // 将e作为p的直接前驱插入
    T remove(ListNodePosi<T> p); // 删除合法位置p处的节点，返回被删除节点的数据项
    /* 去重 */
    int deduplicate(); // 无序去重
// 遍历
    void traverse(void(*visit)(T &)); // 遍历（使用函数指针，只读或局部性修改）
    template<typename VST> void traverse(VST &visit); // 遍历（使用函数对象，可全局性修改）
};

/* 列表初始化，在创建列表对象时统一调用。 */
template<typename T>
void List<T>::init() {
    header = new ListNode<T>;  // 创建头哨兵节点
    trailer = new ListNode<T>; // 创建尾哨兵节点

    header->succ = trailer;  // 初始时，头、尾节点互联
    header->pred = nullptr;  // 头哨兵始终无前驱
    trailer->pred = header;
    trailer->succ = nullptr; // 尾哨兵始终无后继

    _size = 0; // 初始规模为0
}

template<typename T>
void List<T>::copyNodes(ListNodePosi<T> p, int n) { // p合法，且至少有n-1个真后继节点
    init(); // 创建头、尾哨兵节点并做初始化
    while (n-- > 0) {
        insertAsLast(p->data); // 将自位置p起的n项依次作为末节点插入
        p = p->succ;
    }
}

template<typename T>
List<T>::List(List<T> const &L, Rank r, int n) {
    ListNodePosi<T> p = L.first(); // 自首节点出发
    while (r-- > 0) p = p->succ;   // 找到L[r]的位置
    copyNodes(p, n);
}

template<typename T>
int List<T>::clear() {
    int oldSize = _size; // 记录原规模
    while (_size > 0) remove(header->succ); // 反复删除首节点，直至列表变空
    return oldSize; // 返回删除的节点的个数
}

template<typename T>
List<T>::~List<T>() {
    clear();        // 清空列表节点
    delete header;  // 释放头、尾哨兵节点
    delete trailer;
}

/* 重载下标运算符，以通过秩直接访问列表节点（虽方便，效率低，需慎用） */
template<typename T>
T &List<T>::operator[](Rank r) const { // assert: 0 <= r < _size
    ListNodePosi<T> p = first(); // 从首节点出发
    while (r-- > 0) p = p->succ; // 顺数第r个节点即是目标节点
    return p->data; // 返回其中所存元素
}

/* 无序列表区间查找：在节点p的n个前驱中，找到等于e的最后者。 */
template<typename T>
ListNodePosi<T> List<T>::find(T const &e, int n, ListNodePosi<T> p) const {
    while (n-- > 0) { // 对于p的最近的n个前驱，自右向左
        if ((p = p->pred)->data == e) return p; // 逐个比对，直至命中
    }
    return nullptr; // 或p越出左边界，意味着区间内不包含e，查找失败
} // 注：节点p可能是trailer，n个前驱指的是真前驱（哨兵节点并无数据域）

template<typename T>
ListNodePosi<T> List<T>::insertAfter(ListNodePosi<T> p, T const &e) {
    _size++;
    return p->insertAsSucc(e); // 将e作为p的后继插入
}

template<typename T>
ListNodePosi<T> List<T>::insertBefore(ListNodePosi<T> p, T const &e) {
    _size++;
    return p->insertAsPred(e); // 将e作为p的前驱插入
}

template<typename T>
T List<T>::remove(ListNodePosi<T> p) {
    T e = p->data; // 备份待删除节点的数值（假定T类型可以直接赋值）
    p->pred->succ = p->succ;
    p->succ->pred = p->pred; // 前驱节点与后继节点相互链接
    delete p; // 释放节点
    _size--;  // 更新规模
    return e; // 返回备份的数值
}

template<typename T>
int List<T>::deduplicate() {
    int oldSize = _size; // 记录原规模
    ListNodePosi<T> p = first(); // 从首节点开始
    for (Rank r = 0; p != trailer; p = p->succ) {
        ListNodePosi<T> q = find(p->data, r, p); // 在p的r个真前驱中查找雷同者（至多一个）
        q ? remove(q) : r++; // 注意：r为无重前缀的长度，p不断地指向下一节点
    }
    return oldSize - _size; // 向量规模变化量，即被删除元素总数
}

template<typename T>
void List<T>::traverse(void (*visit)(T &)) { // 借助函数指针机制
    for (ListNodePosi<T> p = first(); p != trailer; p = p->succ) { // 遍历列表
        visit(p->data);
    }
}

template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit) { // 借助函数对象机制
    for (ListNodePosi<T> p = first(); p != trailer; p = p->succ) { // 遍历列表
        visit(p->data);
    }
}