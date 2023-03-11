#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* Problem C. ISBN-13 */
int main()
{
	string str;

	while (getline(cin, str)) // 读取一行
	{
		vector<int> result; // 存放结果

		bool right = true;  // 格式正确
		bool single = true; // 奇数行

		for (auto temp : str) // 将字符转换成数字，存入result
		{
			if (temp == ' ') // 跳过空白符
				continue;
			else if (!isdigit(temp)) // 不是数字
			{
				right = false;
				break;
			}
			else
				result.push_back(temp - '0'); // 转换成数字，存入result
		}

		if (result.size() != 12) // 长度有误
			right = false;

		if (right) // 格式正确，处理
		{
			int sum = 0; // 差
			for (auto temp : result) // 求差
			{
				if (single) // 奇数项
					sum += temp;
				else        // 偶数项
					sum += 3 * temp;

				single = !single; // 奇偶反转
			}

			int d13 = 10 - sum % 10; // 校验和

			if (d13 == 10)
				result.push_back(0); // 若校验和为10，则取0。
			else
				result.push_back(d13);

			for (auto temp : result) // 输出结果
				cout << temp;
			cout << endl;
		}
		else
			cout << "Invalid" << endl;
	}
	return 0;
}
