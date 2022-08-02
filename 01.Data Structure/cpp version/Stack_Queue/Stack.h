#pragma once

#include "../Sequence/Vector.h"

/* 栈模板类：利用C++的继承机制，将栈作为向量的派生类，实现栈结构。 */
template<typename T> class Stack : private Vector<T> { // 将向量的首端作为栈底，末端作为栈顶
public: // size()、empty()以及其他开放接口，均可直接沿用
    using Vector<T>::size;
    using Vector<T>::empty;
    using Vector<T>::operator[];
private:
    using Vector<T>::insert;
    using Vector<T>::remove;
public:
    void push(T const &e) { insert(size(), e); } // 入栈：将e插至栈顶，等效于将新元素作为向量的末元素插入
    T pop() { return remove(size() - 1); }       // 出栈：删除栈顶对象，等效于删除向量的末元素
    T &top() { return (*this)[size() - 1]; }     // 取顶：引用栈顶对象，直接返回向量的末元素
};

/* 重载输出运算符：打印栈中的元素（测试时使用）。 */
template<typename T>
std::ostream &operator<<(std::ostream &os, Stack<T> const &S) {
    if (S.empty()) return os << "[ >";
    os << "[ ";
    for (int i = 0; i < S.size() - 1; i++) {
        os << S[i] << ", ";
    }
    os << S[S.size() - 1] << " >";
    return os;
}