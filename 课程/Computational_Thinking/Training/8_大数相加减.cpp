#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

void bigAdd(const string num1, const string num2, vector<int> &result)
{
	/* �ӵ�λ����λ���μ��� */
	auto p1 = num1.rbegin(), p2 = num2.rbegin();
	for (; p1 != num1.rend() && p2 != num2.rend(); p1++, p2++)
		result.push_back((*p1 - '0') + (*p2 - '0'));
	if (p2 == num2.rend())                // num2�϶�
		for (; p1 != num1.rend(); p1++)
			result.push_back(*p1 - '0');
	else                                  // num1�϶�
		for (; p2 != num2.rend(); p2++)
			result.push_back(*p2 - '0');

	/* ��λ���� */
	for (int i = 0; i <= result.size() - 2; i++)
	{
		int temp = result[i] / 10;  // ��Ž�λ����
		result[i] = result[i] % 10; // ����
		result[i + 1] = result[i + 1] + temp; // i+1������size-1��i������size-2
	}

	/* �������λ */
	int *last = &result.back();
	while (*last >= 10) // ���ӷ��Ľ�����ڵ���10����ѽ�λ��1���뵽��һλ�ļ�����
	{
		int temp = *last / 10;  // ��Ž�λ����
		*last = *last % 10;     // ����
		result.push_back(temp);
		last++;
	}
}

void bigSubtract(const string num1, const string num2, vector<int> &result)
{

}

int main()
{
	string line;

	while (getline(cin, line)) // ����һ��
	{
		string num1, num2;
		vector<int> result;
		istringstream buffer(line);  // ��buffer�󶨵��ն������

		while (buffer >> num1 >> num2) // ģ��ӷ�
		{
			/* �������λ */
			bool negative1 = false, negative2 = false;
			if (num1[0] == '-') { negative1 = true; num1.erase(num1.begin()); }
			if (num2[0] == '-') { negative2 = true; num2.erase(num2.begin()); }

			if (negative1 == false && negative2 == false) // ��Ϊ����
				bigAdd(num1, num2, result);
			else if (negative1 == true && negative2 == true) // ��Ϊ����
			{
				bigAdd(num1, num2, result);
				cout << "-"; // �������
			}

			for (auto num = result.rbegin(); num != result.rend(); num++)
				cout << *num;
			cout << endl;
		}
	}



	return 0;
}
