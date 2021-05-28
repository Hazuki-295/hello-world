#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct product // 乘积
{
	// 成员
	long long val; int count; // 乘积、因子数
	// 构造函数
	product(long long _val, int _count) :val(_val), count(_count) {};
};

bool operator<(const product &a, const product &b) // 优先级更弱
{
	if (abs(a.val) < abs(b.val))
		return true;
	else if (abs(a.val) == abs(b.val))
	{
		if (a.count > b.count)
			return true;
		else if (a.count == b.count) // 以正数为准
			if (a.val < b.val)
				return true;
	}

	return false;
}

bool compare(const int &a, const int &b) // a>b? 降序
{
	if (abs(a) > abs(b))
		return true;
	else if (abs(a) == abs(b))
		if (a > b)  // 以正数为准
			return true;

	return false;
} // 降序

/* Problem C. 最大积 */
int main()
{
	// 给定若干个整数S=S1,S2,...,Sn，其中数的最大乘积是多少？

	// 最大乘积，因子有序排列，从大到小乘
	string line; int cases = 0;

	while (getline(cin, line))
	{
		cout << "Case " << ++cases << ":";
		stringstream buffer(line);

		int temp;
		vector<int> factors; // 因子

		while (buffer >> temp)
		{
			if (temp > 0)
				factors.push_back(temp); // 正因子
			else if (temp < 0)
				factors.push_back(temp); // 负因子
		}
		// 不考虑只含有0

		sort(factors.begin(), factors.end(), compare); // 正负因子可混合使用，以绝对值最大为准

		/* 处理因子 */
		vector<product> products;
		long long sum = 0;   // 乘积
		int count = 1;       // 因子数

		if (factors.size() != 0)
		{
			long long temp = 1;
			for (int i = 0; i < factors.size(); i++) // 处理每个因子
			{
				temp = temp * factors[i];
				products.push_back(product(temp, i + 1));
			}
			sort(products.begin(), products.end());
			sum = products.back().val;     // 取出最大乘积
			count = products.back().count; // 及其对应个数
		}

		long long ans = sum; int min = count; // ans为满足要求的最大乘积，min为得到该最大积的最少因数个数

		cout << " " << ans << " " << min << endl;
	}

	return 0;
}
