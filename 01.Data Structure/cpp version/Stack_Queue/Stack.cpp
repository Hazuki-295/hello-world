#include <iostream>
#include <string>
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

/* 进制转换：将十进制数n，转换为base进制。 */
string convert(size_t n, int base) {
    string digit = "0123456789ABCDEF"; // 数位符号，如有必要可相应扩充
    Stack<char> S;  // 辅助栈，逆序计算输出
    while (n > 0) { // 在尚有余数之前，由低到高，逐一计算出新进制下的各数位
        S.push(digit[n % base]); // 余数（当前的最低位）入栈
        n /= base; // n更新为其对base的除商
    }
    string result;
    while (!S.empty()) {
        result.push_back(S.pop()); // 由高位到低位，输出栈中元素
    }
    return result; // 返回转换后的base进制表示
}

template<typename T> class TestStack {
private:
    Stack<T> myStack;
public:
    void testStack();  // 栈操作测试
    void conversion(); // 进制转换
};

template<typename T>
void TestStack<T>::testStack() {
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
}

template<typename T>
void TestStack<T>::conversion() {
    cout << "进制转换：\n";
    int caseCount = 0;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn << "十进制正整数 n，新进制 base：";
        size_t n;
        int base;
        if (cin >> n >> base) {
            string result = convert(n, base);
            cout << prefixOut << "转换完成，新进制表示为：";
            cout << result + '(' + to_string(base) + ')';
            printf("\n\n");
        } else {
            printf("\n\n");
            break;
        }
    }
}

int main() {
    auto obj = new TestStack<int>;
    enum operationType {
        Test, Conversion
    };
    cout << "请输入要执行的操作（01.栈测试 02.进制转换）：";
    int opType;
    cin >> opType;
    cout << endl;
    switch (--opType) {
        case Test: {
            obj->testStack();
            break;
        }
        case Conversion: {
            obj->conversion();
            break;
        }
    }

    return 0;
}