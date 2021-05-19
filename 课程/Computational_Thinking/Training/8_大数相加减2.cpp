#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

void bigAdd(const string num1, const string num2, vector<int> &result) // �����������
{
	/* �ӵ�λ����λ���μ��� */
	auto p1 = num1.begin(), p2 = num2.begin();
	for (vector<int>::size_type i = 0; i < result.size() - 1; i++) // ��֤i+1��vector�Ϸ���Χ
	{
		if (p1 != num1.end() && p2 != num2.end()) // δ�����β
		{
			int temp = (*p1 - '0') + (*p2 - '0');
			result[i] += temp;
			if (result[i] >= 10)
			{
				result[i + 1] = 1; // ��λ
				result[i] %= 10;   // ����
			}
			p1++; p2++;
		}
	}
}

void bigSubtract(const string num1, const string num2, vector<int> &result) // �����������(num1>num2)
{
	/* �ӵ�λ����λ���μ��� */
	auto p1 = num1.begin(), p2 = num2.begin();
	for (vector<int>::size_type i = 0; i < result.size() - 1; i++) // ��֤i+1��vector�Ϸ���Χ
	{
		if (p1 != num1.end() && p2 != num2.end()) // δ�����β
		{
			int temp = (*p1 - '0') - (*p2 - '0');
			result[i] += temp;
			if (result[i] < 0)
			{
				result[i + 1] = -1;  // ��λ
				result[i] += 10;     // ����
			}
			p1++; p2++;
		}
	}
}

int main()
{
	string line;

	while (getline(cin, line)) // ����һ��
	{
		string num1, num2;

		istringstream buffer(line);  // ��buffer�󶨵��ն������

		while (buffer >> num1 >> num2) // ģ��ӷ�
		{
			/* �������λ */
			bool negative1 = false, negative2 = false;
			if (num1[0] == '-') { negative1 = true; num1.erase(num1.begin()); }
			if (num2[0] == '-') { negative2 = true; num2.erase(num2.begin()); }

			auto maxsize = max(num1.size(), num2.size());
			vector<int> result(maxsize + 1); // �����������

			/* Ԥ���� */
			string copy1(num1); string copy2(num2); // �������������ж�ʱʹ��

			reverse(num1.begin(), num1.end()); // ����洢����λ����
			reverse(num2.begin(), num2.end());

			while (num1.size() != maxsize || num2.size() != maxsize) // �����Է��㴦��
			{
				if (num1.size() != maxsize) // ȱ�0
					num1.push_back('0');
				else if (num2.size() != maxsize)
					num2.push_back('0');
			}
			/* Ԥ���� */

			if (negative1 == false && negative2 == false) // ��Ϊ����
				bigAdd(num1, num2, result);
			else if (negative1 == true && negative2 == true) // ��Ϊ����
			{
				bigAdd(num1, num2, result);
				cout << "-"; // �������
			}
			else // һ��һ����
			{
				if (negative1 == false && negative2 == true) // ���Ӹ���
				{
					if (copy1 >= copy2) // �ַ����Ƚ�����
						bigSubtract(num1, num2, result);
					else
					{
						bigSubtract(num2, num1, result);
						cout << "-"; // �������
					}
				}
				else if (negative1 == true && negative2 == false) // ��������
				{
					if (copy1 > copy2) // �ַ����Ƚ�����
					{
						bigSubtract(num1, num2, result);
						cout << "-"; // �������
					}
					else
						bigSubtract(num2, num1, result);
				}
			}

			auto highest = result.end() - 1;
			while (result.size() > 1 && *highest == 0) // ȥ��ǰ׺��0
			{
				result.erase(highest);
				highest = result.end() - 1;
			}

			for (auto num = result.rbegin(); num != result.rend(); num++)
				cout << *num;
			cout << endl;
		}
	}

	return 0;
}