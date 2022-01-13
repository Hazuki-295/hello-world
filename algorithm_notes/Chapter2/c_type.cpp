#include <iostream>
#include <climits>
using namespace std;

int main() {
    int maxNum = INT_MAX;
    long biggerNum = LONG_MAX;
    long long bigNum1 = LLONG_MAX;
    long long bigNum2 = 123456789012345;

    cout << maxNum << "\n"
         << biggerNum << "\n"
         << bigNum1 << "\n"
         << bigNum2 << endl;

    return 0;
}