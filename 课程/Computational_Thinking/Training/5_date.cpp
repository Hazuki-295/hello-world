#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/* ���ڸ�ʽת�� */
int main()
{
	string line; stringstream buffer;

	while (getline(cin, line))
	{
		for (auto &c : line)
			if (c == '-')
				c = ' ';

		string date; // ת���Ľ��������
		istringstream buffer(line); // ��buffer�󶨵��ն������

		vector<string> num; string temp;
		while (buffer >> temp)
			num.push_back(temp);
		if (num.size() == 3) // ��ʽ 2108-01-21 ת��Ϊ 01/21/2108
		{
			if (num[1].size() == 1) // �·�ֻ��һ������
				num[1] = '0' + num[1];
			if (num[2].size() == 1) // ����ֻ��һ������
				num[2] = '0' + num[2];

			date = num[1] + '/' + num[2] + '/' + num[0];
			cout << date << endl;
		}
	}

	return 0;
}
