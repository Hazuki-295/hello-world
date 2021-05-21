#include <iostream>
#include <stack>
using namespace std;

struct Node
{
    int a, b;
    Node(int x, int y):a(x),b(y){}
};

int main()
{
    stack<Node> mystack;
    // mystack.emplace(1, 2); //emplace函数可以将一个元素加入栈中，与push的区别在于：emplace可以直接传入Node的构造函数的参数，并将构造的元素加入栈中
    mystack.push(Node(1,2));        //编译不通过，要达到上面的效果需要手动构造，例如mystack.push(Node(1,2));
    Node p = mystack.top();
    cout << p.a << " " << p.b << endl;

    stack<Node> my2;
    my2.swap(mystack); //swap函数可以交换两个栈的元素
    cout << mystack.size() << " " << my2.size() << endl;

    return 0;
}