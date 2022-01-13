#include <iostream>
#include <climits>
using namespace std;

int main() {
    int num = INT_MAX;
    long varNum = LONG_MAX; // 随操作系统不同。Ubuntu 64 下为 8bytes，Windows 下为 4bytes
    long long bigNum1 = LLONG_MAX;
    long long bigNum2 = 123456789012345; // 字面值类型也随之改变

    cout << num << "\n"
         << varNum << "\n"
         << bigNum1 << "\n"
         << bigNum2 << endl;

    bool boolTest = 5;
    printf("%d\n", boolTest); // 将整型值赋值给bool类型，自动转换成0或1。

    return 0;
}