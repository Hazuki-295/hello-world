#include <iostream>
#include <string>
#include "SqList.h"

using namespace std;

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
    cout << '\n' << endl;

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
        if (!(cin >> opType)) {
            cout << '\n' << endl;
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
        cout << '\n' << endl;
    }

    /* 测试完成，销毁线性表 */
    printf("测试完成，销毁线性表。\n");
    DestroyList(L);

    return 0;
}