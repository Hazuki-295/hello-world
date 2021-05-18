#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

/* (����������)ʮ������תʮ���� */
int HexToDec(string hex)
{
	int sum = 0, temp; bool negative = false;
	int prefix = 2; // ǰ׺������
	if (hex[0] == '-') // ����
	{
		negative = true;
		prefix = 3; // "-0x"
	}
	int exp = (hex.size() - prefix) - 1; // nλ����ָ��Ϊ0,1,2,...,n-1
	for (auto c = hex.begin() + prefix; c != hex.end(); c++) // ����0x
	{
		if (isdigit(*c))
			temp = *c - '0';
		else if (*c >= 'a' && *c <= 'f')
			temp = *c - 'a' + 10;
		else
			temp = *c - 'A' + 10;
		sum = sum + temp * pow(16, exp);
		exp--;
	}
	if (negative)
		sum *= -1;
	return sum;
}

int main()
{
	string line; stringstream buffer;

	while (getline(cin, line)) // ��һ����ʮ�����������
	{
		// int hex_num;
		string hex;                 // ����һ������һ��ʮ����������string����
		istringstream buffer(line); // ��buffer�󶨵��ն������

		int sum = 0;
		// while (buffer >> hex >> hex_num) // ��ȡʮ��������
			// sum = sum + hex_num;
		while (buffer >> hex) // ��ȡʮ��������
			sum = sum + HexToDec(hex);
		cout << sum << endl;
	}

	return 0;
}
