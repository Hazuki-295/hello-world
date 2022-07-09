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
    /* 排序算法（为方便测试，改为开放接口） */
    void insertionSort(ListNodePosi<T> p, int n); // 插入排序
    void selectionSort(ListNodePosi<T> p, int n); // 选择排序
    ListNodePosi<T> merge(ListNodePosi<T> p, int n, List<T> &L, ListNodePosi<T> q, int m); // 二路归并算法
    void mergeSort(ListNodePosi<T> &p, int n); // 归并排序（p将指向归并后区间的新起点）

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
    const T &operator[](Rank r) const; // 重载，支持循秩访问（效率低）
    /* 查找接口 */
    bool valid(ListNodePosi<T> p) { return p && trailer != p && header != p; } // 判断位置p是否对外合法（将头、尾节点等同与nullptr）
    ListNodePosi<T> find(T const &e) const { return find(e, _size, trailer); } // 无序列表整体查找
    ListNodePosi<T> find(T const &e, int n, ListNodePosi<T> p) const; // 无序列表区间查找
    ListNodePosi<T> search(T const &e) const { return search(e, _size, trailer); } // 有序列表整体查找
    ListNodePosi<T> search(T const &e, int n, ListNodePosi<T> p) const; // 有序列表区间查找
    ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); // 在p及其n-1个后继中选出最大者
    ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); } // 整体最大者
// 可写访问接口
    /* 插入与删除 */
    ListNodePosi<T> insertAsFirst(T const &e) { return insertAfter(header, e); }  // 将e作为首节点插入
    ListNodePosi<T> insertAsLast(T const &e) { return insertBefore(trailer, e); } // 将e作为末节点插入
    ListNodePosi<T> insertAfter(ListNodePosi<T> p, T const &e);  // 将e作为p的直接后继插入
    ListNodePosi<T> insertBefore(ListNodePosi<T> p, T const &e); // 将e作为p的直接前驱插入
    T remove(ListNodePosi<T> p); // 删除合法位置p处的节点，返回被删除节点的数据项
    /* 去重 */
    int deduplicate(); // 无序去重
    int uniquify();    // 有序去重
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
template<typename T> // assert: 0 <= r < _size
const T &List<T>::operator[](Rank r) const { // O(r)效率低下，可偶尔为之，却不宜常用
    ListNodePosi<T> p = first(); // 从首节点出发
    while (r-- > 0) p = p->succ; // 顺数第r个节点即是目标节点（秩 == 前驱的总数）
    return p->data; // 返回其中所存元素
}

/* 无序列表区间查找：在节点p的n个真前驱中，找到等于e的最后者。 */
template<typename T>
ListNodePosi<T> List<T>::find(T const &e, int n, ListNodePosi<T> p) const {
    while (n-- > 0) { // 对于p的最近的n个前驱，自右向左
        if ((p = p->pred)->data == e) return p; // 逐个比对，直至命中
    }
    return nullptr; // 或p越出左边界，意味着区间内不包含e，查找失败
} // 注：节点p可能是trailer，n个前驱指的是真前驱（亦即，不包括自己）

/* 有序列表区间查找：在节点p的n个真前驱中，找到不大于e的最后者。 */
template<typename T>
ListNodePosi<T> List<T>::search(T const &e, int n, ListNodePosi<T> p) const {
    while (n-- >= 0) { // 对于p的最近的n个前驱，自右向左
        if ((p = p->pred)->data <= e) break; // 逐个比对，直至命中（第一个不大于e的节点）
    }
    return p; // 返回查找终止的位置；或范围越界，返回区间左边界的前驱（可能是header）
} // 注：与无序列表find()不同的一个细微之处是，while多循环了一次
// 如此在范围越界时，最后一次关键码比较没有意义（等效于与-inf比较），但符合输出语义约定

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
    p->succ->pred = p->pred; // 前驱节点与后继节点相互链接，跳过节点p
    delete p; // 释放已经孤立出来的节点p
    _size--;  // 更新规模
    return e; // 返回备份的数值
}

template<typename T>
int List<T>::deduplicate() {
    int oldSize = _size; // 记录原规模
    ListNodePosi<T> p = first(); // 从首节点开始
    for (Rank r = 0; p != trailer; p = p->succ) {      // 自前向后逐个考查各节点
        if (ListNodePosi<T> q = find(p->data, r, p)) { // 在p的r个真前驱中查找雷同者（至多一个）
            remove(q);
        } else r++; // 注意：r为无重前缀的长度，p不断地指向下一节点
    }
    return oldSize - _size; // 列表规模变化量，即被删除元素总数
}

template<typename T>
int List<T>::uniquify() {
    if (_size < 2) return 0; // 平凡列表自然无重复
    int oldSize = _size;     // 记录原规模
    ListNodePosi<T> p = first(), q; // 双指针，p为各区段起点，q则为其后继
    while ((q = p->succ) != trailer) { // 反复考察相邻的节点对(p, q)
        if (p->data == q->data) { // 若雷同，删除后者
            remove(q);
        } else p = q; // 否则（互异），转向下一区段
    }
    return oldSize - _size; // 列表规模变化量，即被删除元素总数
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

/* 插入排序算法：对列表中起始于位置p、宽度为n的区间做插入排序。 */
template<typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n) {
    for (int r = 0; r < n; r++) { // 逐一为各节点（r为有序前缀的长度）
        insertAfter(search(p->data, r, p), p->data); // 查找适当的位置并插入
        p = p->succ;        // 首先使p转向下一节点
        remove(p->pred); // 移除已经向前插入的元素
    }
}

/* 选择排序算法：对列表中起始于位置p、宽度为n的区间做选择排序。 */
template<typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n) {
    ListNodePosi<T> head = p->pred, tail = p; // 双指针，分别指向区间首、尾哨兵
    for (int i = 0; i < n; i++) { // 待排序区间为(head, tail)
        tail = tail->succ;        // 使tail到达区间尾部哨兵
    }
    while (n > 1) { // 至少还剩下两个节点时，在待排序区间内
        ListNodePosi<T> max = selectMax(head->succ, n); // 找出最大者（雷同时秩大者优先）
        insertBefore(tail, remove(max)); // 将其移至无序区间末尾（作为有序区间新的首元素）
        tail = tail->pred; // 待排序区间缩小，有序后缀扩大
        n--;
    } // 剩下一个节点时，自然是最小元素
}

template<typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n) {
    ListNodePosi<T> max = p; // 暂定最大者为首节点p
    for (ListNodePosi<T> cur = p; n > 1; n--) {     // 逐一考察p的n-1个真后继
        if ((cur = cur->succ)->data >= max->data) { // 若当前元素不小于max
            max = cur; // 更新最大元素位置记录
        }
    }
    return max; // 返回最大节点位置
}

/* 归并排序算法：对起始于位置p的n个元素排序。 */
template<typename T>
void List<T>::mergeSort(ListNodePosi<T> &p, int n) { // valid(p) && rank(p) + n <= size
    if (n < 2) return; // 递归基，单元素区间自然有序，否则...
    int m = n >> 1;    // 以中点为界
    ListNodePosi<T> q = p;
    for (int i = 0; i < m; i++) { // 均分列表，找到后子列表起点L[m]
        q = q->succ;
    }
    mergeSort(p, m);        // 对前子列表排序[0, m)
    mergeSort(q, n - m); // 对后子列表排序[m, n)
    p = merge(p, m, *this, q, n - m); // 归并
} // 注意：排序后，由于mergeSort()传入的是引用参数，merge()返回更新的首节点，p依然指向归并后区间的（新）起点

/* 有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并。 */
template<typename T>
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, int n, List<T> &L, ListNodePosi<T> q, int m) {
    ListNodePosi<T> head = p->pred; // 归并之后p可能不再指向首节点，故需先记忆，以便在返回前更新
    while ((m > 0) && (p != q)) {   // q尚未出界之前；或是在mergeSort()中，p越至q的位置，可提前退出
        if ((n > 0) && (p->data <= q->data)) { // 若p尚未出界且v(p) <= v(q)，则
            p = p->succ; // p直接后移，即完成归入
            n--;
        } else { // 否则，将q转移至p之前，以完成归入
            insertBefore(L.remove((q = q->succ)->pred), p);
            m--;
        }
    } // while条件不成立时，p == q仅可能发生在p一直后移直到 n == 0，即原本就两区间整体有序，此时可直接跳过
    return head->succ; // 返回更新的首节点
}