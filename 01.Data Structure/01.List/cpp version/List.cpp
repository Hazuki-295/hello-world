#include <iostream>
#include "List.h"

using namespace std;

template<typename T>
void print(List<T> &L) { // 打印列表
    cout << '[';
    ListNodePosi<T> p = L.first();
    for (int i = 0; i < L.size() - 1; i++) {
        cout << p->data << ", ";
        p = p->succ;
    }
    cout << p->data << ']';
}

template<typename T>
ListNodePosi<T> nodePosi(List<T> &L, Rank r) { // 返回列表中秩为r的节点的位置
    ListNodePosi<T> p = L.first();
    while (r-- > 0) p = p->succ;
    return p;
}

int main() {
    using T = char;
    List<T> myList;

    /* 初始化列表 */
    printf("初始化列表：\n");
    printf("[1] 请输入列表中初始元素的个数：");
    int length;
    cin >> length;
    printf("[2] 请输入%d个初始元素：", length);
    T temp;
    for (int i = 0; i < length; i++) {
        cin >> temp;
        myList.insertAsLast(temp);
    }
    printf("[3] 列表初始化完成。当前列表长度为：%d，列表中的元素为：", myList.size());
    print(myList);
    printf("\n\n");

    /* 列表操作测试 */
    enum operationType {
        Insert, Remove, Search, Sort, Permute, Deduplicate
    };
    printf("列表操作测试：\n");
    int caseCount = 0, opType;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn;
        printf("请输入将要执行的操作（01.插入 02.删除）：");
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
                if (insertPos >= 1 && insertPos <= myList.size() + 1) {
                    myList.insertBefore(nodePosi(myList, insertPos - 1), temp);
                    printf("插入操作完成。\n");
                } else {
                    printf("插入失败。插入的位置非法。\n");
                }
                break;
            }
            case Remove: {
                cout << prefixWhitespace << "删除操作。\n";
                cout << prefixWhitespace << "请输入删除的位置：";
                int removePos;
                cin >> removePos;

                cout << prefixOut;
                if (removePos >= 1 && removePos <= myList.size()) {
                    temp = myList.remove(nodePosi(myList, removePos - 1));
                    printf("删除操作完成。删除的元素的值为：");
                    cout << temp << endl;
                } else {
                    printf("删除失败。删除的位置非法。\n");
                }
                break;
            }
            default: {
                cout << prefixOut << "输入的操作数错误。" << endl;
            }
        }

        /* 当次操作后输出列表 */
        cout << prefixWhitespace;
        printf("当前列表长度为：%d，列表中的元素为：", myList.size());
        print(myList);
        printf("\n\n");
    }

    return 0;
}