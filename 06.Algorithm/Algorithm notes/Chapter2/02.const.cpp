#include <iostream>
using namespace std;

#define ADD(a, b) ((a) + (b))              // 必须加那么多括号，防止运算优先级出错。
#define MAX(a, b) ((a) > (b) ? (a) : (b))  // 因为宏定义是直接原封不动替换，然后再进行编译和运行。

const int INT_MAX = (1 << 31) - 1;  // 实际的 int 最大值的表达式，2147483647。(位运算符优先级较低)
const int INF_NUM = (1 << 30) - 1;  // 用来表示“无穷大”的数，同时防止相加时溢出。可等价地定义为 0x3fffffff

int main() {
    int num1 = 3, num2 = 5;
    printf("add(3, 5) = %d\n", ADD(num1, num2));
    printf("max(3, 5) = %d\n", MAX(num1, num2));

    cout << INT_MAX << '\n'
         << INF_NUM * 2 << endl;  // const 表达式在预编译阶段就会进行计算，所以此处不会出错

    return 0;
}