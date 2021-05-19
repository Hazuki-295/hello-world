#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

void bigAdd(const string num1, const string num2, vector<int> &result) // 两大正数相加
{
	/* 从低位到高位依次计算 */
	auto p1 = num1.begin(), p2 = num2.begin();
	for (vector<int>::size_type i = 0; i < result.size() - 1; i++) // 保证i+1在vector合法范围
	{
		if (p1 != num1.end() && p2 != num2.end()) // 未到达结尾
		{
			int temp = (*p1 - '0') + (*p2 - '0');
			result[i] += temp;
			if (result[i] >= 10)
			{
				result[i + 1] = 1; // 进位
				result[i] %= 10;   // 余数
			}
			p1++; p2++;
		}
	}
}

void bigSubtract(const string num1, const string num2, vector<int> &result) // 两大正数相减(num1>num2)
{
	/* 从低位到高位依次计算 */
	auto p1 = num1.begin(), p2 = num2.begin();
	for (vector<int>::size_type i = 0; i < result.size() - 1; i++) // 保证i+1在vector合法范围
	{
		if (p1 != num1.end() && p2 != num2.end()) // 未到达结尾
		{
			int temp = (*p1 - '0') - (*p2 - '0');
			result[i] += temp;
			if (result[i] < 0)
			{
				result[i + 1] = -1;  // 借位
				result[i] += 10;     // 余数
			}
			p1++; p2++;
		}
	}
}

int main()
{
	string line;

	while (getline(cin, line)) // 处理一行
	{
		string num1, num2;

		istringstream buffer(line);  // 将buffer绑定到刚读入的行

		while (buffer >> num1 >> num2) // 模拟加法
		{
			/* 处理符号位 */
			bool negative1 = false, negative2 = false;
			if (num1[0] == '-') { negative1 = true; num1.erase(num1.begin()); }
			if (num2[0] == '-') { negative2 = true; num2.erase(num2.begin()); }

			auto maxsize = max(num1.size(), num2.size());
			vector<int> result(maxsize + 1); // 创建结果数组

			/* 预处理 */
			string copy1(num1); string copy2(num2); // 拷贝，作正负判断时使用

			reverse(num1.begin(), num1.end()); // 倒序存储，各位对齐
			reverse(num2.begin(), num2.end());

			while (num1.size() != maxsize || num2.size() != maxsize) // 扩充以方便处理
			{
				if (num1.size() != maxsize) // 缺项补0
					num1.push_back('0');
				else if (num2.size() != maxsize)
					num2.push_back('0');
			}
			/* 预处理 */

			if (negative1 == false && negative2 == false) // 均为正数
				bigAdd(num1, num2, result);
			else if (negative1 == true && negative2 == true) // 均为负数
			{
				bigAdd(num1, num2, result);
				cout << "-"; // 输出负号
			}
			else // 一正一负，
			{
				if (negative1 == false && negative2 == true) // 正加负。
				{
					if (copy1 >= copy2) // 字符串比较性质
						bigSubtract(num1, num2, result);
					else
					{
						bigSubtract(num2, num1, result);
						cout << "-"; // 输出负号
					}
				}
				else if (negative1 == true && negative2 == false) // 负加正。
				{
					if (copy1 > copy2) // 字符串比较性质
					{
						bigSubtract(num1, num2, result);
						cout << "-"; // 输出负号
					}
					else
						bigSubtract(num2, num1, result);
				}
			}

			auto highest = result.end() - 1;
			while (result.size() > 1 && *highest == 0) // 去掉前缀的0
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