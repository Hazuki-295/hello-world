#include <iostream>
#include <string>
#include "LinkList.h"

using namespace std;

int main() {
    LinkList L;
    InitList(L);

    /* 初始化链表 */
    printf("初始化链表：\n");
    enum InitType {
        ListHeadInsert, ListTailInsert
    };
    printf("[1] 请输入链表的初始化方式（01.头插法 02.尾插法）：");
    int opType;
    cin >> opType;
    printf("[2] 请输入链表中初始元素的个数：");
    int length;
    cin >> length;
    printf("[3] 请输入%d个初始元素：", length);
    ElemType temp;
    switch (--opType) {
        case ListHeadInsert:
            List_HeadInsert(L, length);
            break;
        case ListTailInsert:
            List_TailInsert(L, length);
            break;
        default:
            cout << "输入的操作数错误。" << endl;
            exit(1);
    }
    printf("[4] 链表初始化完成。当前链表长度为：%d，链表中的元素为：", Length(L));
    PrintList(L);
    cout << '\n' << endl;

    /* 链表操作测试 */
    enum operationType {
        Insert, Delete, Locate, Get, HeadInsert, TailInsert
    };
    printf("链表操作测试：\n");
    int caseCount = 0;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn;
        printf("请输入将要执行的操作（01.插入 02.删除 03.按值查找 04.按位查找 05.头插法重构链表 06.尾插法重构链表）：");
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
                ListNode *p = LocateElem(L, temp);
                if (p != nullptr) {
                    printf("查找成功。链表中存在该元素。\n");
                } else {
                    printf("查找失败。链表中不存在该元素。\n");
                }
                break;
            }
            case Get: {
                cout << prefixWhitespace << "按位查找操作。\n";
                cout << prefixWhitespace << "请输入要查找的元素的位序：";
                int pos;
                cin >> pos;

                cout << prefixOut;
                ListNode *p = GetElem(L, pos);
                if (p != nullptr && p != L) {
                    temp = p->data;
                    printf("查找成功。该元素的值为：");
                    cout << temp << endl;
                } else {
                    printf("查找失败。该位序不合法。\n");
                }
                break;
            }
            case HeadInsert: {
                cout << prefixWhitespace << "头插法重构链表。\n";
                cout << prefixWhitespace << "请输入链表中初始元素的个数：";
                cin >> length;
                cout << prefixWhitespace << "请输入" << length << "个初始元素：";
                List_HeadInsert(L, length);

                cout << prefixOut << "头插法重构链表完成。" << endl;
                break;
            }
            case TailInsert: {
                cout << prefixWhitespace << "尾插法重构链表。\n";
                cout << prefixWhitespace << "请输入链表中初始元素的个数：";
                cin >> length;
                cout << prefixWhitespace << "请输入" << length << "个初始元素：";
                List_TailInsert(L, length);

                cout << prefixOut << "尾插法重构链表完成。" << endl;
                break;
            }
            default: {
                cout << prefixOut << "输入的操作数错误。" << endl;
            }
        }

        /* 当次操作后输出链表 */
        cout << prefixWhitespace;
        printf("当前链表长度为：%d，链表中的元素为：", Length(L));
        PrintList(L);
        cout << '\n' << endl;
    }

    /* 测试完成，销毁链表 */
    printf("测试完成，销毁链表。\n");
    DestroyList(L);

    return 0;
}