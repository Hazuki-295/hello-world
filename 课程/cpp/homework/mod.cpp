#include <iostream>
using namespace std;

bool mod(int a, int b, int &result)
{
	if (b == 0)
	{
		cout << "错误，除数为0。";
		return false;
	}
	result = a - (a / b) * b;
	return true;
}

int main()
{
	int a, b, result;
	cout << "取余运算 a \% b。\n";
	cout << "请输入两个整数 a 和 b\n";

	if (cin >> a >> b)
	{
		if (mod(a, b, result))
		{
			cout << "a \% b = " << result << endl;
		}
		if (result == (a % b))
		{
			cout << "求余数方程正确。\n";
		}
	}
	else
		cout << "输入错误！\n";
	return 0;

}