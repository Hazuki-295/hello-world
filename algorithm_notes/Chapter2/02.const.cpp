#include <iostream>
#define ADD(a, b) ((a) + (b))              // 必须加那么多括号，防止运算优先级出错。
#define MAX(a, b) ((a) > (b) ? (a) : (b))  // 因为宏定义是直接原封不动替换，然后再进行编译和运行。

const int INF = (1 << 30) - 1;  // 用来表示无穷大的数，同时防止相加时溢出。可等价地定义为 0x3fffffff (位运算符优先级较低)

int main() {
    int num1 = 3, num2 = 5;
    printf("add(3, 5) = %d\n", ADD(num1, num2));
    printf("max(3, 5) = %d\n", MAX(num1, num2));

    return 0;
}