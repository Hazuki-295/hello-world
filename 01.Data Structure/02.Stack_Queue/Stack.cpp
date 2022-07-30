#include <iostream>
#include "SqStack.h"
#include "LinkStack.h"

using namespace std;

ostream &operator<<(ostream &os, SqStack const &S) {
    if (StackEmpty(S)) return os << "[ >";
    int length = S.top + 1;
    os << "[ ";
    for (int i = 0; i < length - 1; i++) {
        os << S.data[i] << ", ";
    }
    os << S.data[length - 1] << " >";
    return os;
}

ostream &operator<<(ostream &os, LinkStack const &S) {
    if (StackEmpty(S)) return os << "< ]";
    os << "< ";
    ListNode *p = S.head;
    while ((p = p->next) != nullptr) {
        os << p->data;
        if (p->next != nullptr) os << ", ";
    }
    return os << " ]";
}

int StackLength(SqStack S) {
    return S.top + 1;
}

int StackLength(LinkStack S) {
    return Length(S.head); // 单链表表长
}

template<typename Stack> void testStack() {
    // SqStack myStack;
    Stack myStack;
    InitStack(myStack);

    /* 初始化栈 */
    printf("初始化栈：\n");
    printf("[1] 请输入栈中初始元素的个数：");
    int length;
    cin >> length;
    printf("[2] 请输入%d个初始元素：", length);
    ElemType temp;
    for (int i = 0; i < length; i++) {
        cin >> temp;
        Push(myStack, temp);
    }
    printf("[3] 栈初始化完成。当前栈中元素个数为：%d，栈中的元素为：", StackLength(myStack));
    cout << myStack << '\n' << endl;

    /* 栈操作测试 */
    enum operationType {
        _Push, _Pop, _Top
    };
    printf("栈操作测试：\n");
    int caseCount = 0, opType;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn << "请输入将要执行的操作（01.入栈 02.出栈 03.取顶）：";
        if (!(cin >> opType)) {
            cout << '\n' << endl;
            break;
        }
        switch (--opType) {
            case _Push: {
                cout << prefixWhitespace << "入栈操作。\n";
                cout << prefixWhitespace << "请输入入栈的元素：";
                cin >> temp;

                cout << prefixOut;
                Push(myStack, temp);
                printf("入栈操作完成。\n");
                break;
            }
            case _Pop: {
                cout << prefixWhitespace << "出栈操作。\n";

                cout << prefixOut;
                if (!StackEmpty(myStack)) {
                    temp = Pop(myStack);
                    printf("出栈操作完成，出栈的栈顶元素为：");
                    cout << temp << endl;
                } else {
                    printf("出栈操作失败，当前栈为空栈。\n");
                }
                break;
            }
            case _Top: {
                cout << prefixWhitespace << "取顶操作。\n";

                cout << prefixOut;
                if (!StackEmpty(myStack)) {
                    temp = GetTop(myStack);
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
        printf("当前栈中元素个数为：%d，栈中的元素为：", StackLength(myStack));
        cout << myStack << '\n' << endl;
    }

    /* 测试完成，销毁栈 */
    printf("测试完成，销毁栈。\n");
    DestroyStack(myStack);
}

int main() {
    enum StackType {
        _SqStack, _LinkStack
    };

    cout << "栈测试，请选择栈的实现（01.SqStack 02.LinkStack）：";
    int opType;
    cin >> opType;
    cout << endl;

    switch (--opType) {
        case _SqStack:
            testStack<SqStack>();
            break;
        case _LinkStack:
            testStack<LinkStack>();
            break;
        default:
            cout << "输入的操作数错误。" << endl;
    }

    return 0;
}