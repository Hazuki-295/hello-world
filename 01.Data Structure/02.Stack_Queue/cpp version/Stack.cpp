#include <iostream>
#include "Stack.h"

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, Stack<T> const &S) {
    os << '[';
    for (int i = 0; i < S.size() - 1; i++) {
        os << S[i] << ", ";
    }
    os << S[S.size() - 1] << ']';
    return os;
}

template<typename T>
void print(Stack<T> &S) { // 打印栈中元素
    cout << S;
}

int main() {
    using T = int;
    Stack<T> myStack;

    /* 初始化栈 */
    printf("初始化栈：\n");
    printf("[1] 请输入栈中初始元素的个数：");
    int length;
    cin >> length;
    printf("[2] 请输入%d个初始元素：", length);
    T temp;
    for (int i = 0; i < length; i++) {
        cin >> temp;
        myStack.push(temp);
    }
    printf("[3] 栈初始化完成。当前栈中元素个数为：%d，栈中的元素为：", myStack.size());
    print(myStack);
    printf("\n\n");

    /* 栈操作测试 */
    enum operationType {
        Push, Pop, Top
    };
    printf("栈操作测试：\n");
    int caseCount = 0, opType;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn;
        printf("请输入将要执行的操作（01.入栈 02.出栈 03.取顶）：");
        if (scanf("%d", &opType) == EOF) {
            printf("\n\n");
            break;
        }
        switch (--opType) {
            case Push: {
                cout << prefixWhitespace << "入栈操作。\n";
                cout << prefixWhitespace << "请输入入栈的元素：";
                cin >> temp;

                cout << prefixOut;
                myStack.push(temp);
                printf("入栈操作完成。\n");
                break;
            }
            case Pop: {
                cout << prefixWhitespace << "出栈操作。\n";

                cout << prefixOut;
                if (!myStack.empty()) {
                    temp = myStack.pop();
                    printf("出栈操作完成，出栈的栈顶元素为：");
                    cout << temp << endl;
                } else {
                    printf("出栈操作失败，当前栈为空栈。\n");
                }
                break;
            }
            case Top: {
                cout << prefixWhitespace << "取顶操作。\n";

                cout << prefixOut;
                if (!myStack.empty()) {
                    temp = myStack.top();
                    printf("取顶操作完成，当前栈顶元素为：");
                    cout << temp << endl;
                } else {
                    printf("取顶操作失败，当前栈为空栈。\n");
                }
                break;
            }
            default: {
                cout << prefixOut << "输入的操作数错误。" << endl;
            }
        }

        /* 当次操作后输出栈 */
        cout << prefixWhitespace;
        printf("当前栈中元素个数为：%d，栈中的元素为：", myStack.size());
        print(myStack);
        printf("\n\n");
    }

    return 0;
}