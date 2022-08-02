#pragma once

#include "../Sequence/List.h"

/* 队列模板类：利用C++的继承机制，将队列作为列表的派生类，实现队列结构。 */
template<typename T> class Queue : private List<T> { // 将列表的首节点作为队头，末节点作为队尾
public: // size()、empty()以及其他开放接口，均可直接沿用
    using List<T>::size;
    using List<T>::empty;
    using List<T>::first;
private:
    using List<T>::insertAsLast;
    using List<T>::remove;
public:
    void enqueue(T const &e) { insertAsLast(e); } // 入队：将e插至队尾
    T dequeue() { return remove(first()); }       // 出队：删除队首元素
    T &front() { return first()->data; }          // 队首：返回队首对象的引用
};

/* 重载输出运算符：打印队列中的元素（测试时使用）。 */
template<typename T>
std::ostream &operator<<(std::ostream &os, Queue<T> const &Q) {
    if (Q.empty()) return os << "< ]";
    os << "< ";
    ListNodePosi<T> p = Q.first();
    for (int i = 0; i < Q.size() - 1; i++) {
        os << p->data << ", ";
        p = p->succ;
    }
    os << p->data << " ]";
    return os;
}