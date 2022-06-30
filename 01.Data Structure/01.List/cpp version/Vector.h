#pragma once

using Rank = int; // 秩
#define DEFAULT_CAPACITY 3 // 默认的初始容量（实际应用中可设置为更大）

template<typename T>
class Vector {      // 向量模板类
protected:
    Rank _size;     // 规模，当前有效元素的数量
    Rank _capacity; // 容量大小
    T *_elem;       // 数据区

    void copyFrom(T const *A, Rank lo, Rank hi); // 复制数组区间A[lo, hi)

public:
// 构造函数
    /* 默认构造函数，容量为c、规模为s、所有元素初始化为v。 */
    Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v); // s<=c
    }

    Vector(T const *A, Rank n) { copyFrom(A, 0, n); }       // 数组整体复制
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } // 数组区间复制
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }         // 向量整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } // 向量区间复制
// 析构函数
    ~Vector() { delete[] _elem; } // 释放内部空间
}; // Vector

/* 以数组区间A[lo, hi)为蓝本复制向量，由Vector的基于复制的构造函数调用。 */
template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)]; // 分配空间，以初始规模的双倍容量申请
    _size = 0; // 规模清零
    while (lo < hi) { // A[lo, hi)内的元素逐一复制至_elem[0, hi - lo)
        _elem[_size++] = A[lo++];
    }
} // 用const修饰，保证A中的元素不致被篡改；运行时间 = O(hi - lo)
