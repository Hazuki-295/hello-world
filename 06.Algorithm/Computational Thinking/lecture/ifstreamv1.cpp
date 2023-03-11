#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
using namespace std;
int n;
int main()
{
    //freopen("in.txt","r",stdin);
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    int sum = 0;
    while (true)
    {
        if (cin.eof())
            break;
        //读入已16进制
        cin >> hex >> n;
        sum += n;
    }
    //格式化输出。

    cout << showbase << oct << n << "(Oct)," << dec << sum << "(Dec),"
         << hex << setiosflags(ios::uppercase) << sum << "(Hex)" << endl;
    return 0;
}