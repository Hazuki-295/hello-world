#include <iostream>
using namespace std;

int main() {
    int maxNum = __INT_MAX__;
    long biggerNum = __LONG_MAX__;
    long long bigNum1 = __LONG_LONG_MAX__;
    long long bigNum2 = 123456789012345;

    cout << maxNum << "\n"
         << biggerNum << "\n"
         << bigNum1 << "\n"
         << bigNum2 << endl;

    return 0;
}