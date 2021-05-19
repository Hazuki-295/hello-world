#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

void bigAdd(const string num1, const string num2, vector<int> &result)
{
	/* 从低位到高位依次计算 */
	auto p1 = num1.rbegin(), p2 = num2.rbegin();
	for (; p1 != num1.rend() && p2 != num2.rend(); p1++, p2++)
		result.push_back((*p1 - '0') + (*p2 - '0'));
	if (p2 == num2.rend())                // num2较短
		for (; p1 != num1.rend(); p1++)
			result.push_back(*p1 - '0');
	else                                  // num1较短
		for (; p2 != num2.rend(); p2++)
			result.push_back(*p2 - '0');

	/* 进位处理 */
	for (int i = 0; i <= result.size() - 2; i++)
	{
		int temp = result[i] / 10;  // 存放进位的数
		result[i] = result[i] % 10; // 余数
		result[i + 1] = result[i + 1] + temp; // i+1最大等于size-1，i最大等于size-2
	}

	/* 处理最大位 */
	int *last = &result.back();
	while (*last >= 10) // 若加法的结果大于等于10，则把进位的1加入到下一位的计算中
	{
		int temp = *last / 10;  // 存放进位的数
		*last = *last % 10;     // 余数
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

	while (getline(cin, line)) // 处理一行
	{
		string num1, num2;
		vector<int> result;
		istringstream buffer(line);  // 将buffer绑定到刚读入的行

		while (buffer >> num1 >> num2) // 模拟加法
		{
			/* 处理符号位 */
			bool negative1 = false, negative2 = false;
			if (num1[0] == '-') { negative1 = true; num1.erase(num1.begin()); }
			if (num2[0] == '-') { negative2 = true; num2.erase(num2.begin()); }

			if (negative1 == false && negative2 == false) // 均为正数
				bigAdd(num1, num2, result);
			else if (negative1 == true && negative2 == true) // 均为负数
			{
				bigAdd(num1, num2, result);
				cout << "-"; // 输出负号
			}

			for (auto num = result.rbegin(); num != result.rend(); num++)
				cout << *num;
			cout << endl;
		}
	}



	return 0;
}
