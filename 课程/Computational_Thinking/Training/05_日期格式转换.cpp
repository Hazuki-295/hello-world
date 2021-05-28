#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/* 日期格式转换 */
int main()
{
	string line; stringstream buffer;

	while (getline(cin, line))
	{
		for (auto &c : line)
			if (c == '-')
				c = ' ';

		string date; // 转换的结果，日期
		istringstream buffer(line); // 将buffer绑定到刚读入的行

		vector<string> num; string temp;
		while (buffer >> temp)
			num.push_back(temp);
		if (num.size() == 3) // 格式 2108-01-21 转换为 01/21/2108
		{
			if (num[1].size() == 1) // 月份只有一个数字
				num[1] = '0' + num[1];
			if (num[2].size() == 1) // 日期只有一个数字
				num[2] = '0' + num[2];

			date = num[1] + '/' + num[2] + '/' + num[0];
			cout << date << endl;
		}
	}

	return 0;
}
