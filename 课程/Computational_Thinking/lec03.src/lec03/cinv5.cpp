#include <iostream>
using namespace std;
int main()
{
    char ch, str[20];
    cin.getline(str, 5);
    cout << "flag1:" << cin.good() << endl; // 查看goodbit状态，即是否有异常
    cin.clear();                            // 清除错误标志
    cout << "flag1:" << cin.good() << endl; // 清除标志后再查看异常状态
    cin >> ch;
    cout << "str:" << str << endl;
    cout << "ch:" << ch << endl;
    return 0;
}
