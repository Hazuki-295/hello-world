#include <iostream>
#include <stack>
using namespace std;

void hexadecimal(int number)
{
	stack<char> S; int index;

	char hexa[17];
	for (int i = 0; i <= 9; i++)
	{
		hexa[i] = '0' + i;
	}
	for (int i = 10; i <= 16; i++)
	{
		hexa[i] = 'a' + (i - 10);
	}

	while (number)
	{
		index = number % 16;
		S.push(hexa[index]);
		number = number / 16;
	}

	while (!S.empty())
	{
		cout << S.top();
		S.pop();
	}
	cout << endl;
}

int main()
{
	cout << "请输入一个十进制数，它将被转换成十六进制数。\n";
	int n; cin >> n;// 41775
	cout << "转换成的十六进制数：\n";
	hexadecimal(n);
	cout << "cout输出结果为：\n";
	cout << hex << n << endl;
	return 0;
}