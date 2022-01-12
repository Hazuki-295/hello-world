#include <iostream>
#include <limits>
using namespace std;
int main()
{
    char str1[20] = {NULL}, str2[20] = {NULL};
    cin.getline(str1, 5);
    cin.clear(); // 清除错误标志 
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //清除缓冲区的当前行
    cin.getline(str2, 20);
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    return 0;
}
