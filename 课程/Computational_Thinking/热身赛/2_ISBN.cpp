#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* Problem C. ISBN-13 */
int main()
{
	string str;

	while (getline(cin, str)) // ��ȡһ��
	{
		vector<int> result; // ��Ž��

		bool right = true;  // ��ʽ��ȷ
		bool single = true; // ������

		for (auto temp : str) // ���ַ�ת�������֣�����result
		{
			if (temp == ' ') // �����հ׷�
				continue;
			else if (!isdigit(temp)) // ��������
			{
				right = false;
				break;
			}
			else
				result.push_back(temp - '0'); // ת�������֣�����result
		}

		if (result.size() != 12) // ��������
			right = false;

		if (right) // ��ʽ��ȷ������
		{
			int sum = 0; // ��
			for (auto temp : result) // ���
			{
				if (single) // ������
					sum += temp;
				else        // ż����
					sum += 3 * temp;

				single = !single; // ��ż��ת
			}

			int d13 = 10 - sum % 10; // У���

			if (d13 == 10)
				result.push_back(0); // ��У���Ϊ10����ȡ0��
			else
				result.push_back(d13);

			for (auto temp : result) // ������
				cout << temp;
			cout << endl;
		}
		else
			cout << "Invalid" << endl;
	}
	return 0;
}
