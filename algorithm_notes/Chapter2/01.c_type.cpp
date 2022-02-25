#include <iostream>
#include <climits>
using namespace std;

int main() {
    /* 整型 */
    int num = INT_MAX;                    /* 数量级：10^9 */
    long varNum = LONG_MAX;               // 随操作系统不同。Ubuntu 64 下为 8bytes，Windows 下为 4bytes
    long long bigNum = LLONG_MAX;         /* 数量级：10^18 */
    long long literal = 123456789012345;  // 字面值的类型也随之改变

    cout << "整型:\n"
         << num << "\n"
         << varNum << "\n"
         << bigNum << endl;

    bool boolTest = 5;         // (隐式类型转换) 将整型值赋值给bool类型，自动转换成0或1。
    printf("%d\n", boolTest);  // 当然，在实际使用时，直接给布尔变量赋值 true 或 false 就行。

    /* 浮点型 */
    float fl = 3.1415;         // 有效精度：6～7 位
    double db = 3.1415926536;  // 有效精度：15～16 位
    printf("浮点型: %f, %f\n", fl, db);  // 不指定时，默认显示6位小数

    /*****************************************************************************
     * 总结：
     * 1. 简单来说，需要记住的是：
     *      看到题目要求 10^9 以内，或者说 32 位整数，就用 int 型来存放；
     *      如果是 10^18 以内 (例如 10^10)，或者说 64 位整数，就要用 long long 型来存放。
     * 2. 对浮点型来说，只需要记住一点：
     *      不要使用 float，碰到浮点型的数据都应该用 double 来存储。
     *****************************************************************************/

    return 0;
}