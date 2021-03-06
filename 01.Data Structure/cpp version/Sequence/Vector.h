#pragma once

#include <iostream> // 引入swap()和rand()

using Rank = int; // 秩
#define DEFAULT_CAPACITY 3 // 默认的初始容量（实际应用中可设置为更大）

template<typename T> class Vector { // 向量模板类
protected:
    Rank _size;     // 规模，当前有效元素的数量
    Rank _capacity; // 容量大小
    T *_elem;       // 数据区

    void copyFrom(T const *A, Rank lo, Rank hi); // 复制数组区间A[lo, hi)
    void expand(); // 空间不足时扩容
    void shrink(); // 装填因子过小时缩容
public:
    /* 排序算法（为方便测试，改为开放接口） */
    bool bubble(Rank lo, Rank hi);     // 一趟扫描交换
    void bubbleSort(Rank lo, Rank hi); // 起泡排序算法
    void merge(Rank lo, Rank mi, Rank hi); // 二路归并算法
    void mergeSort(Rank lo, Rank hi);      // 归并排序

public:
// 构造函数
    Vector(int s = 0, T v = T{}) { // 默认构造函数，规模为s、所有元素初始化为v
        _capacity = (s == 0) ? DEFAULT_CAPACITY : s;
        _elem = new T[_capacity];
        for (_size = 0; _size < s; _elem[_size++] = v); // s<=c
    }

    /* 基于复制的构造函数 */
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); } // 数组整体复制
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } // 数组区间复制
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); } // 拷贝构造函数，向量整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } // 向量区间复制
// 析构函数
    ~Vector() { delete[] _elem; } // 释放内部空间
// 只读访问接口
    Rank size() const { return _size; }   // 规模
    bool empty() const { return !_size; } // 判空
    Rank find(T const &e) const { return find(e, 0, _size); } // 无序向量整体查找
    Rank find(T const &e, Rank lo, Rank hi) const; // 无序向量区间查找
    Rank search(T const &e) const { return search(e, 0, _size); } // 有序向量整体查找
    Rank search(T const &e, Rank lo, Rank hi) const;  // 有序向量区间查找
// 可写访问接口
    /* 运算符重载 */
    T &operator[](Rank r) { return _elem[r]; } // 重载下标操作符，可以类似于数组形式引用各元素
    const T &operator[](Rank r) const { return _elem[r]; } // 仅限于做右值的重载版本
    Vector<T> &operator=(Vector<T> const &); // 重载赋值操作符，以便直接克隆向量
    /* 插入与删除 */
    T remove(Rank r); // 删除秩为r的元素
    int remove(Rank lo, Rank hi); // 删除秩在区间[lo, hi)之内的元素
    Rank insert(Rank r, T const &e); // 插入元素
    Rank insert(T const &e) { return insert(_size, e); } // 默认作为末元素插入
    /* 排序与置乱 */
    void sort(Rank lo, Rank hi);    // 对[lo, hi)排序
    void sort() { sort(0, _size); } // 整体排序
    void unsort(Rank lo, Rank hi);      // 对[lo, hi)置乱
    void unsort() { unsort(0, _size); } // 整体置乱
    /* 去重 */
    Rank deduplicate(); // 无序去重
    Rank uniquify();    // 有序去重
// 遍历
    void traverse(void(*visit)(T &));  // 遍历（使用函数指针，只读或局部性修改）
    template<typename VST> void traverse(VST &visit); // 遍历（使用函数对象，可全局性修改）
}; // Vector

/* 以数组区间A[lo, hi)为蓝本复制向量，由Vector的基于复制的构造函数以及重载的赋值运算符调用。 */
template<typename T> // T为基本类型，或已重载赋值操作符'='
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)]; // 分配空间，以初始规模的双倍容量申请
    _size = 0; // 规模清零
    while (lo < hi) { // A[lo, hi)内的元素
        _elem[_size++] = A[lo++]; // 逐一复制至_elem[0, hi - lo)
    }
} // 用const修饰，保证A中的元素不致被篡改

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &V) { // 深复制
    if (_elem) { delete[] _elem; } // 释放原有内容
    copyFrom(V._elem, 0, V._size); // 整体复制
    return *this; // 返回当前对象的引用，以便链式赋值
}

template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return; // 是否确实需要扩容，采用“懒惰”策略
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; // 不致低于最小容量
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1]; // 容量加倍
    for (Rank i = 0; i < _size; i++) {
        _elem[i] = oldElem[i]; // 复制原向量内容（T为基本类型，或已重载赋值操作符'='）
    }
    delete[] oldElem; // 释放原空间
}

template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return; // 不致收缩到最小容量以下
    if (_size << 2 > _capacity) return; // 是否装填因子过小，以25%为界
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1]; // 容量减半
    for (Rank i = 0; i < _size; i++) {
        _elem[i] = oldElem[i]; // 复制原向量内容
    }
    delete[] oldElem; // 释放原空间
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    switch (rand() % 2) {
        case 1: {
            bubbleSort(lo, hi); // 起泡排序
            break;
        }
        default: {
            mergeSort(lo, hi); // 归并排序
            break;
        }
    }
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    T *V = _elem + lo; // 起始地址，将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
    for (Rank i = hi - lo; i > 0; i--) {    // 自后向前
        std::swap(V[i - 1], V[rand() % i]); // 将V[i - 1]与V[0, i)中某一元素随机交换
    }
}

/* 无序向量的顺序查找：返回最后一个元素e的位置；失败时，返回lo - 1 */
template<typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const { // assert: 0 <= lo < hi <= _size
    while ((lo < hi--) && (e != _elem[hi])); // 从后向前，顺序查找
    return hi; // 若hi < lo，则意味着失败，返回lo - 1；否则hi即命中元素的秩
}

/* 在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩 */
template<typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const { // assert: 0 <= lo < hi <= _size
    return binarySearch(_elem, e, lo, hi);
}

/* 二分查找算法：在有序向量的区间[lo, hi)内查找元素e */
template<typename T> static
Rank binarySearch(T *A, T const &e, Rank lo, Rank hi) { // assert 0 <= lo <= hi <= _size
    while (lo < hi) { // 不变性：A[0, lo) <= e < A[hi, n)
        Rank mi = (lo + hi) >> 1; // 以中点为轴点
        (e < A[mi]) ? hi = mi : lo = mi + 1; // 经比较后确定深入[lo, mi)或(mi, hi)
    } // 成功查找不能提前终止
    return --lo; // 循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
} // 有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置

template<typename T>
Rank Vector<T>::insert(Rank r, T const &e) { // assert: 0 <= r <= size
    expand(); // 若有必要，扩容
    for (Rank i = _size; i > r; i--) {
        _elem[i] = _elem[i - 1]; // 自后向前，后继元素顺次后移一个单元
    }
    _elem[r] = e; // 插入位置置入新元素
    _size++;  // 更新容量
    return r; // 返回秩
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) return 0; // 出于效率考虑，单独处理退化情况，比如remove(0, 0)
    while (hi < _size) {    // 区间[hi, _size)的元素
        _elem[lo++] = _elem[hi++]; // 顺次前移hi - lo个单元
    } // 期间覆盖区间[lo, hi)。执行结束后，lo为实际向量尾部哨兵
    _size = lo; // 更新规模，直接丢弃尾部[lo, _size = hi)区间
    shrink();   // 若有必要，则缩容
    return hi - lo; // 返回被删除元素的数目
}

template<typename T>
T Vector<T>::remove(Rank r) { // assert: 0 <= r < size
    T e = _elem[r];   // 备份被删除元素
    remove(r, r + 1); // 调用区间删除算法，等效于对区间[r, r + 1)的删除
    return e; // 返回被删除元素
}

template<typename T>
Rank Vector<T>::deduplicate() {
    Rank oldSize = _size; // 记录原规模
    for (Rank i = 1; i < _size;) { // 从_elem[1]开始，自前向后逐个考查各元素_elem[i]
        if (find(_elem[i], 0, i) < 0) { // 在其前缀[0, i)中寻找与之雷同者（至多一个）
            i++;          // 若无雷同者则继续考查其后继
        } else remove(i); // 否则删除雷同者
    }
    return oldSize - _size; // 向量规模变化量，即被删除元素总数
}

template<typename T>
Rank Vector<T>::uniquify() {
    Rank i = 0, j = 0; // 各对互异“相邻”元素的秩（i和j分别指向一对相邻子区间的首元素）
    while (++j < _size) { // 逐一扫描，直至末元素
        if (_elem[i] != _elem[j]) { // 跳过雷同者
            _elem[++i] = _elem[j];  // 发现不同元素时，向前移至紧邻于前者右侧
        }
    }
    _size = ++i;  // 使i指向实际向量的哨兵位置，直接截断尾部多余元素
    shrink();     // 若有必要，则缩容
    return j - i; // 向量规模变化量，即被删除元素总数
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T &)) { // 借助函数指针机制
    for (Rank i = 0; i < _size; i++) visit(_elem[i]); // 遍历向量
}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &visit) { // 借助函数对象机制
    for (Rank i = 0; i < _size; i++) visit(_elem[i]); // 遍历向量
}

/* 起泡排序算法 */
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) { // assert: 0 <= lo < hi <= size
    while (!bubble(lo, hi--)); //逐趟做扫描交换，直至全序
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) { // 一趟扫描交换
    bool sorted = true; // 整体有序标志
    while (++lo < hi) { // 自左向右，逐一检查各对相邻元素
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false; // 若逆序，则意味着尚未整体有序
            std::swap(_elem[lo - 1], _elem[lo]); // 并需要通过交换使局部有序
        }
    }
    return sorted; // 返回有序标志
}

/* 归并排序算法 */
template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) { // assert: 0 <= lo < hi <= size
    if (hi - lo < 2) return;  // 递归基，单元素区间自然有序，否则...
    Rank mi = (lo + hi) >> 1; // 以中点为界
    mergeSort(lo, mi); // 对前半段排序
    mergeSort(mi, hi); // 对后半段排序
    merge(lo, mi, hi); // 归并
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) { // 各自有序的子向量[lo, mi)和[mi, hi)
    T *A = _elem + lo; // 原地保存，合并后的有序向量A[0, hi - lo) = _elem[lo, hi)
    T *C = _elem + mi; // 原地保存，后子向量C[0, lc) = _elem[mi, hi)

    int lengthB = mi - lo, lengthC = hi - mi;
    T *B = new T[lengthB]; // 辅助数组，前子向量B[0, lb) <-- _elem[lo, mi)
    for (Rank i = 0; i < lengthB; i++) B[i] = A[i]; // 拷贝前子向量

    Rank i = 0, j = 0, k = 0;
    while ((j < lengthB) && (k < lengthC)) {       // 未有向量被耗尽
        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++]; // B[j]和C[k]中的小者续至A末尾
    }
    while (j < lengthB) { // 若C先耗尽，则
        A[i++] = B[j++];  // 将B残余的后缀归入A中
    } // 若B先耗尽，由于C原地保存，无需操作

    delete[] B; // 释放临时空间
}