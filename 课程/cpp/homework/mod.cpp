#include <iostream>
using namespace std;

bool mod(int a, int b, int &result)
{
	if (b == 0)
	{
		cout << "���󣬳���Ϊ0��";
		return false;
	}
	result = a - (a / b) * b;
	return true;
}

int main()
{
	int a, b, result;
	cout << "ȡ������ a \% b��\n";
	cout << "�������������� a �� b\n";

	if (cin >> a >> b)
	{
		if (mod(a, b, result))
		{
			cout << "a \% b = " << result << endl;
		}
		if (result == (a % b))
		{
			cout << "������������ȷ��\n";
		}
	}
	else
		cout << "�������\n";
	return 0;

}