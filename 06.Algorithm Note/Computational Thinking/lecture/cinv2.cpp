#include <string> 
#include <iostream> 
using namespace std;
int main()
{
    char a;
    int b;
    float c;
    string str;
    cin >> a >> b >> c >> str;
    cout << a << " " << b << " " << c << " " << str << endl;
    string test;
    getline(cin, test); //不阻塞
    cout << "test:" << test << endl;
    return 0;
}
