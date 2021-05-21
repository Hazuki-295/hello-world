#include <iostream>
#include <stack>
using namespace std;

int main()
{
    stack<int> mystack;

    for (int i = 0; i < 5; ++i)
        mystack.push(i);    //push函数将参数元素加入栈中，没有返回值
    cout << "Stack size: " << mystack.size() << endl; //size函数返回栈的大小

    while (!mystack.empty()) //empty函数返回一个bool值，栈为空时返回true，否则返回false
    {
        cout << ' ' << mystack.top(); //top函数的返回值是栈顶元素（注意并没有删掉栈顶元素）
        mystack.pop();                //pop函数将栈顶元素删掉，没有返回值
    }
    cout << endl;

    return 0;
}