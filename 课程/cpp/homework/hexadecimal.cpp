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
	cout << "������һ��ʮ��������������ת����ʮ����������\n";
	int n; cin >> n;// 41775
	cout << "ת���ɵ�ʮ����������\n";
	hexadecimal(n);
	cout << "cout������Ϊ��\n";
	cout << hex << n << endl;
	return 0;
}