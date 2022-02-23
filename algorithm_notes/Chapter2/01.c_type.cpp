#include <iostream>
#include <climits>
using namespace std;

int main() {
    /* 整型 */
    int num = INT_MAX;                    /* 数量级：10^9 */
    long varNum = LONG_MAX;               // 随操作系统不同。Ubuntu 64 下为 8bytes，Windows 下为 4bytes
    long long bigNum1 = LLONG_MAX;        /* 数量级：10^18 */
    long long bigNum2 = 123456789012345;  // 字面值的类型也随之改变

    cout << "整型：\n"
         << num << "\n"
         << varNum << "\n"
         << bigNum1 << "\n"
         << bigNum2 << endl;

    bool boolTest = 5;         // (隐式类型转换) 将整型值赋值给bool类型，自动转换成0或1。
    printf("%d\n", boolTest);  // 当然，在实际使用时，直接给布尔变量赋值 true 或 false 就行。

    /* 浮点型 */
    float fl = 3.1415;         // 有效精度：6～7 位
    double db = 3.1415926536;  // 有效精度：15～16 位
    printf("浮点型：%f, %f\n", fl, db);  // 不指定时，默认显示6位小数

    return 0;
}