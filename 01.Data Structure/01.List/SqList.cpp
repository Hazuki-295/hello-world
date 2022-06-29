#include <iostream>

using namespace std;

typedef int ElemType;

/* 线性表的顺序表示（顺序表） */
typedef struct {
    ElemType *data; // 顺序表中的元素，动态分配
    int MaxSize;    // 顺序表的最大容量
    int length;     // 当前元素个数，线性表表长
} SqList;           // 顺序表的类型定义

/* 插入操作。在表L中的第i个位置上插入指定元素e。 */
bool ListInsert(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1) { // 插入的位置非法
        return false;
    }
    if (L.length >= L.MaxSize) { // 当前存储空间已满，不能插入
        return false;
    }

    ElemType *p, *q;      // p和q为辅助指针
    q = &(L.data[i - 1]); // q为插入位置
    for (p = &(L.data[L.length - 1]); p >= q; p--) { // 插入位置及之后的元素右移
        *(p + 1) = *p;
    }
    *q = e;     // 在插入位置q插入新的元素e
    L.length++; // 线性表表长加1
    return true;
}

/* 删除操作。删除表L中第i个位置上的元素，并用e返回删除元素的值。 */
bool ListDelete(SqList &L, int i, ElemType &e) {
    if (i < 1 || i > L.length) { // 删除的位置非法
        return false;
    }

    ElemType *p, *q;             // p和q为辅助指针
    p = &(L.data[i - 1]);        // p为被删除元素的位置
    e = *p;                      // 被删除元素的值赋给e
    q = &(L.data[L.length - 1]); // 表尾元素的位置
    for (p++; p <= q; p++) {     // 被删除元素之后的元素左移，覆盖
        *(p - 1) = *p;
    }
    L.length--; // 线性表表长减1
    return true;
}

/* 按值查找操作。在表L中查找具有给定关键字值的元素，返回其位序。 */
int LocateElem(SqList L, ElemType e) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == e) {
            return i + 1; // 下标为i的元素值等于e，返回其位序i+1
        }
    }
    return 0; // 退出循环，说明查找失败（0并非有效位序）
}

/* 初始化表。构造一个空的线性表。 */
void InitList(SqList &L) {
    L.MaxSize = 10;
    L.data = new ElemType[L.MaxSize];
    L.length = 0;
}

/* 求表长。返回线性表L的长度，即L中数据元素的个数。 */
int Length(SqList L) {
    return L.length;
}

/* 按位查找操作。找到表L中第i个位置的元素，并用e返回其值。 */
bool GetElem(SqList L, int i, ElemType &e) {
    if (i < 1 || i > L.length) { // 查找的位置非法
        return false;
    }
    e = L.data[i - 1]; // 位序为i的元素，其下标为i-1
    return true;
}

/* 输出操作。按前后顺序输出线性表L的所有元素的值。 */
void PrintList(SqList L) {
    for (int i = 0; i < L.length - 1; i++) {
        cout << L.data[i] << ' ';
    }
    cout << L.data[L.length - 1] << endl;
}

/* 判空操作。若L为空表，则返回true，否则返回false。 */
bool Empty(SqList L) {
    return L.length == 0;
}

/* 销毁操作。销毁线性表，并释放线性表L所占用的内存空间。 */
void DestroyList(SqList &L) {
    delete[] L.data;
}