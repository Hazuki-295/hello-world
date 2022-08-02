#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "Stack.h"

using namespace std;

/* 进制转换：将十进制正整数n，转换为base进制。 */
string convert(unsigned long n, int base) {
    string digit = "0123456789ABCDEF"; // 数位符号，如有必要可相应扩充
    Stack<char> S;  // 辅助栈，存放逆序计算出的输出
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

/* 括号匹配：表达式括号匹配检查，可兼顾三种括号。 */
bool parentheses(string exp) {
    Stack<char> S; // 辅助栈，记录已发现但尚未匹配的左括号
    for (int i = 0; i < exp.length(); i++) { // 逐一检查当前字符
        switch (exp[i]) {
            case '(':
            case '[':
            case '{':
                S.push(exp[i]); // 左括号直接入栈
                break;
            case ')':
                if (S.empty() || S.pop() != '(') { // 若栈S提前变空，或右括号与栈顶失配，则表达式必不匹配
                    return false;
                }
                break;
            case ']':
                if (S.empty() || S.pop() != '[') {
                    return false;
                }
                break;
            case '}':
                if (S.empty() || S.pop() != '{') {
                    return false;
                }
                break;
            default:
                break; // 非括号字符一律忽略
        }
    }
    return S.empty(); // 整个表达式扫描过后，栈中若仍残留左括号，则不匹配；否则（栈空）匹配
}

/* 栈混洗：给定入栈序列pushed，判断出栈序列popped能否在执行合法的栈操作序列后得出。 */
template<typename T>
bool validateStackSequences(Vector<T> &pushed, Vector<T> &popped) {
    if (pushed.size() != popped.size()) {
        return false;
    }

    Stack<T> stack; // 辅助中转栈S
    int index = 0;  // 出栈序列下标
    for (int i = 0; i < pushed.size(); i++) { // 模拟进出栈
        stack.push(pushed[i]); // 每入栈一个元素，就随即判断其是否为
        while (!stack.empty() && stack.top() == popped[index]) { // 待出栈元素
            stack.pop();
            index++;
        }
    }
    return stack.empty(); // 若为合法的栈操作序列，则压入中转栈S的pushed序列元素应全部出栈
}

/* 表达式求值：支持的操作符包括 '+'、'-'、'*'、'/'、'(' 和 ')'，返回计算结果。 */
class Evaluate {
private:
    static const size_t NUM_OF_OPERATOR = 7;
    enum Operator {
        ADD, SUB, MUL, DIV, L_P, R_P, EOE
    };
    unordered_map<char, Operator> Operators = {
            {'+',  ADD}, {'-',  SUB}, {'*',  MUL}, {'/',  DIV},
            {'(',  L_P}, {')',  R_P}, {'\0', EOE},
    };
    Vector<string> RPN; // Reverse Polish Notation

    /* 运算符优先等级 [栈顶] [当前] */
    const char priority[NUM_OF_OPERATOR][NUM_OF_OPERATOR] = {
            /*          |----------- 当 前 运 算 符 -----------| */
            /*              +    -    *    /    (    )   \0    */
            /* 一  + */    '>', '>', '<', '<', '<', '>', '>',
            /* 栈  - */    '>', '>', '<', '<', '<', '>', '>',
            /* 顶  * */    '>', '>', '>', '>', '<', '>', '>',
            /* 运  / */    '>', '>', '>', '>', '<', '>', '>',
            /* 算  ( */    '<', '<', '<', '<', '<', '=', ' ',
            /* 符  ) */    ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            /* 一 \0 */    '<', '<', '<', '<', '<', ' ', '='
    };

public:
    int evaluate(string exp); // 表达式求值
    char orderBetween(char stackTop, char op); // 优先级判断
    string postfixExpression(); // 逆波兰表达式
};

int Evaluate::evaluate(string exp) {
    exp.erase(remove(exp.begin(), exp.end(), ' '), exp.end()); // 移除空格
    exp.push_back('\0'); // 尾哨兵
    auto S = exp.begin();

    Stack<int> operands;   // 运算数栈
    Stack<char> operators; // 运算符栈

    operators.push('\0'); // 简化处理，尾哨兵也作为头哨兵首先入栈
    while (!operators.empty()) { // 在运算符栈非空之前，逐个处理表达式中字符
        if (isdigit(*S)) { // 若当前字符为操作数，则
            string substring;
            while (isdigit(*S)) {
                substring.push_back(*S);
                S++;
            }
            int digit = stoi(substring);
            operands.push(digit);             // 读入操作数
            RPN.insert(to_string(digit)); // 并将其接至RPN末尾
        } else { // 若当前字符为运算符，则
            switch (orderBetween(operators.top(), *S)) { // 视其与栈顶运算符之间优先级高低分别处理
                case '<': // 栈顶运算符优先级更低时
                    operators.push(*S); // 计算推迟，当前运算符进栈
                    S++;
                    break;
                case '=': // 优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                    operators.pop(); // 脱括号，并接受下一个字符
                    S++;
                    break;
                case '>': { // 栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
                    char op = operators.pop(); // 栈顶运算符出栈
                    RPN.insert(string(1, op)); // 并将其接至RPN末尾
                    /* 所有运算符均为二元运算符 */
                    int operand2 = operands.pop(); // 取出两个操作数
                    int operand1 = operands.pop();
                    switch (op) { // 实施二元运算，并将结果入栈
                        case '+':
                            operands.push(operand1 + operand2);
                            break;
                        case '-':
                            operands.push(operand1 - operand2);
                            break;
                        case '*':
                            operands.push(operand1 * operand2);
                            break;
                        case '/':
                            operands.push(operand1 / operand2);
                            break;
                        default:
                            exit(1);
                    } // switch
                    break;
                } // case '>'
                default:
                    exit(1); // 逢语法错误，不做处理直接退出
            } // switch
        } // else
    } // while
    return operands.pop(); // 弹出并返回最后的计算结果
}

char Evaluate::orderBetween(char stackTop, char op) {
    return priority[Operators[stackTop]][Operators[op]];
}

string Evaluate::postfixExpression() {
    stringstream buffer;
    for (int i = 0; i < RPN.size() - 1; i++) {
        buffer << RPN[i] << ' ';
    }
    buffer << RPN[RPN.size() - 1];
    return buffer.str();
}

template<typename T> class TestStack {
private:
    Stack<T> myStack;
public:
    void testStack();  // 栈操作测试
    void conversion(); // 进制转换
    void parenthesesMatching(); // 括号匹配
    void stackPermutation(); // 栈混洗
    void calculator(); // 表达式求值
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
    cout << myStack << '\n' << endl;

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

        cout << prefixIn << "请输入将要执行的操作（01.入栈 02.出栈 03.取顶）：";
        if (!(cin >> opType)) {
            cout << '\n' << endl;
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
        cout << myStack << '\n' << endl;
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
        unsigned long n;
        int base;
        if (cin >> n >> base) {
            string result = convert(n, base);
            cout << prefixOut << "进制转换完成，新进制表示为：";
            cout << result + '(' + to_string(base) + ')';
            printf("\n\n");
        } else {
            printf("\n\n");
            break;
        }
    }
}

template<typename T>
void TestStack<T>::parenthesesMatching() {
    cout << "括号匹配：\n";
    int caseCount = 0;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn << "请输入表达式：";
        string exp;
        if (getline(cin, exp)) {
            if (parentheses(exp)) {
                cout << prefixOut << "括号匹配成功。";
            } else {
                cout << prefixOut << "括号匹配失败，此表达式不合法。";
            }
            printf("\n\n");
        } else {
            printf("\n\n");
            break;
        }
    }
}

template<typename T>
void TestStack<T>::stackPermutation() {
    cout << "栈混洗：\n";
    int caseCount = 0;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        Vector<T> pushed, popped;
        cout << prefixIn << "栈中元素个数：";
        int n;
        if (!(cin >> n)) {
            printf("\n\n");
            break;
        }

        T temp;
        cout << prefixWhitespace << "入栈序列 pushed：";
        for (int i = 0; i < n; i++) {
            cin >> temp;
            pushed.insert(temp);
        }

        cout << prefixWhitespace << "出栈序列 popped：";
        for (int i = 0; i < n; i++) {
            cin >> temp;
            popped.insert(temp);
        }

        if (validateStackSequences(pushed, popped)) {
            cout << prefixOut << "合法的出栈序列，此出栈序列为入栈序列的栈混洗。";
        } else {
            cout << prefixOut << "非法的出栈序列，此出栈序列并非入栈序列的栈混洗。";
        }
        printf("\n\n");
    }
}

template<typename T>
void TestStack<T>::calculator() {
    cout << "表达式求值：\n";
    int caseCount = 0;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn << "中缀表达式：";
        string exp;
        if (getline(cin, exp)) {
            auto obj = new Evaluate;
            int result = obj->evaluate(exp);
            cout << prefixOut << "计算完成，表达式计算结果：" << result << endl;
            cout << prefixWhitespace << "后缀表达式：" << obj->postfixExpression();
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
        Test, Conversion, ParenthesesMatching, StackPermutation, Calculator
    };
    cout << "请输入要执行的操作（01.栈测试 02.进制转换 03.括号匹配 04.栈混洗 05.表达式求值）：";
    int opType;
    cin >> opType;
    string empty;
    getline(cin, empty); // 空行
    switch (--opType) {
        case Test:
            obj->testStack();
            break;
        case Conversion:
            obj->conversion();
            break;
        case ParenthesesMatching:
            obj->parenthesesMatching();
            break;
        case StackPermutation:
            obj->stackPermutation();
            break;
        case Calculator:
            obj->calculator(); // (( 0 + (1 + 23) / 4 * 5 * 67 - 8 + 9 ))
            break;
        default:
            cout << "输入的操作数错误。" << endl;
    }

    return 0;
}