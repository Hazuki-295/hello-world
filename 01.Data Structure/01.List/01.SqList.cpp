#include <iostream>
#include <string>

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
    L.MaxSize = 50;
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
    cout << '[';
    for (int i = 0; i < L.length - 1; i++) {
        cout << L.data[i] << ", ";
    }
    cout << L.data[L.length - 1] << ']';
}

/* 判空操作。若L为空表，则返回true，否则返回false。 */
bool Empty(SqList L) {
    return L.length == 0;
}

/* 销毁操作。销毁线性表，并释放线性表L所占用的内存空间。 */
void DestroyList(SqList &L) {
    delete[] L.data;
}

int main() {
    SqList L;
    InitList(L);

    /* 初始化线性表 */
    printf("初始化线性表：\n");
    printf("[1] 请输入线性表中初始元素的个数：");
    int length;
    cin >> length;
    printf("[2] 请输入%d个初始元素：", length);
    ElemType temp;
    for (int i = 0; i < length; i++) {
        cin >> temp;
        ListInsert(L, i + 1, temp);
    }
    printf("[3] 线性表初始化完成。当前线性表长度为：%d，线性表中的元素为：", Length(L));
    PrintList(L);
    printf("\n\n");

    /* 线性表操作测试 */
    enum operationType {
        Insert, Delete, Locate, Get
    };
    printf("线性表操作测试：\n");
    int caseCount = 0, opType;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn;
        printf("请输入将要执行的操作（01.插入 02.删除 03.按值查找 04.按位查找）：");
        if (scanf("%d", &opType) == EOF) {
            printf("\n\n");
            break;
        }
        switch (--opType) {
            case Insert: {
                cout << prefixWhitespace << "插入操作。\n";
                cout << prefixWhitespace << "请输入插入的位置：";
                int insertPos;
                cin >> insertPos;
                cout << prefixWhitespace << "请输入插入的元素：";
                cin >> temp;

                cout << prefixOut;
                if (ListInsert(L, insertPos, temp)) {
                    printf("插入成功。\n");
                } else {
                    printf("插入失败。插入的位置非法。\n");
                }
                break;
            }
            case Delete: {
                cout << prefixWhitespace << "删除操作。\n";
                cout << prefixWhitespace << "请输入删除的位置：";
                int deletePos;
                cin >> deletePos;

                cout << prefixOut;
                if (ListDelete(L, deletePos, temp)) {
                    printf("删除成功。删除的元素的值为：");
                    cout << temp << endl;
                } else {
                    printf("删除失败。删除的位置非法。\n");
                }
                break;
            }
            case Locate: {
                cout << prefixWhitespace << "按值查找操作。\n";
                cout << prefixWhitespace << "请输入要查找的值：";
                cin >> temp;

                cout << prefixOut;
                int pos = LocateElem(L, temp);
                if (pos != 0) {
                    printf("查找成功。第一个值等于给定值的元素的位序为：%d\n", pos);
                } else {
                    printf("查找失败。线性表中不存在该元素。\n");
                }
                break;
            }
            case Get: {
                cout << prefixWhitespace << "按位查找操作。\n";
                cout << prefixWhitespace << "请输入要查找的元素的位序：";
                int pos;
                cin >> pos;

                cout << prefixOut;
                if (GetElem(L, pos, temp)) {
                    printf("查找成功。该元素的值为：%d\n", temp);
                } else {
                    printf("查找失败。该位序不合法。\n");
                }
                break;
            }
            default: {
                cout << prefixOut << "输入的操作数错误。" << endl;
            }
        }

        /* 当次操作后输出线性表 */
        cout << prefixWhitespace;
        printf("当前线性表长度为：%d，线性表中的元素为：", Length(L));
        PrintList(L);
        printf("\n\n");
    }

    /* 测试完成，销毁线性表 */
    printf("测试完成，销毁线性表。\n");
    DestroyList(L);

    return 0;
}