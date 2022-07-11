#include <iostream>

using namespace std;

/* 顺序列表模板类 */
template<typename T> class List {

private:
    using ElemType = T;

    /* 线性表的顺序存储结构(静态大小) */
    ElemType *data;      // 存储空间基址
    int MaxSize, length; // 顺序表的最大容量和当前元素个数(长度)

public:
    // 构造函数
    List(int MaxSize = 50) { InitList(MaxSize); } // 默认

    /* 初始化一个空的顺序表(为顺序表分配存储空间) */
    void InitList(int MaxSize = 50) {
        this->MaxSize = MaxSize;
        data = new ElemType[MaxSize];
        length = 0;  // 空表长度为0
    }

    /* 初始创建有n个元素的顺序表 */
    bool CreatList(int n) {
        if (n > MaxSize) {
            return false;
        }

        ElemType temp;
        length = n;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            data[i] = temp;
        }
        return true;
    }

    /* 插入操作，在表L中第x个位置之前插入新的数据元素e */
    bool ListInsert(int x, ElemType e) {
        if (x < 1 || x > length + 1) // 插入的位置非法
            return false;

        if (length >= MaxSize) // 当前存储空间已满，不能插入
            return false;

        ElemType *p, *q;    // p和q为辅助指针
        q = &(data[x - 1]); // q为插入位置
        for (p = &(data[length - 1]); p >= q; p--) { // 插入位置及之后的元素右移
            *(p + 1) = *p;
        }
        *q = e;      // 在插入位置 q 插入新的元素e
        length++;    // 表长加1
        return true;
    }

    /* 删除操作，删除表L中第x个位置的元素，并用e返回删除元素的值 */
    bool ListDelete(int x, ElemType &e) {
        if (x < 1 || x > length) // 删除的位置非法
            return false;

        ElemType *p, *q; // p和q为辅助指针

        p = &(data[x - 1]);        // p为被删除元素的位置
        e = *p;                    // 被删除元素的值赋给e
        q = &(data[length - 1]);   // 表尾元素的位置
        for (p++; p <= q; p++) {   // 被删除元素之后的元素左移，覆盖
            *(p - 1) = *p;
        }
        length--;   // 表长减1
        return true;
    }

    /* 按值查找操作，在表L中查找具有给定关键字(e)值的元素，返回其位序 */
    int LocateElem(ElemType e) {
        for (int i = 0; i < length; i++) {
            if (data[i] == e) {
                return i + 1; // 下标为i的元素值等于e，返回其位序i+1。
            }
        }
        return 0; // 退出循环，说明查找失败(0表示未找到)
    }

    /* 按位查找操作，找到表L中第i个位置的元素，并用e返回其值 */
    bool GetElem(int x, ElemType &e) {
        if (x < 1 || x > length)
            return false;
        e = data[x - 1]; // 位序为i的元素，其下标为i-1。
        return true;
    }

    /* 输出操作，顺序输出线性表L的所有元素值 */
    void PrintList() {
        for (int i = 0; i < length; i++) {
            cout << data[i] << ' ';
        }
        cout << endl;
    }

    int LinkLength() { return length; };

    void ListTest();
}; // SqList

template<typename T> void List<T>::ListTest() {
    cout << "请输入链表结点个数：" << endl;
    int n;
    cin >> n;
    cout << '\n';

    cout << "请输入" << n << "个链表元素：\n";
    CreatList(n);

    cout << "\n初始化完成。\n";
    /* 测试代码 */
    cout << "当前链表长度为：\n" << LinkLength() << '\n';
    cout << "当前链表元素为：\n";
    PrintList();
    cout << "\n\n";

    /* 操作测试 */
    int delete1, insert1;
    ElemType temp;
    cout << "删除第x个元素：";
    cin >> delete1;
    ListDelete(delete1, temp);
    /* 测试代码 */
    cout << "当前链表长度为：\n" << LinkLength() << '\n';
    cout << "当前链表元素为：\n";
    PrintList();
    cout << "\n\n";

    cout << "在第x个元素之前插入元素：";
    cin >> insert1;
    cout << "插入的元素：";
    cin >> temp;
    ListInsert(insert1, temp);
    /* 测试代码 */
    cout << "当前链表长度为：\n" << LinkLength() << '\n';
    cout << "当前链表元素为：\n";
    PrintList();
    cout << "\n\n";
}

int main() {
    List<int> L;
    L.ListTest();
}
