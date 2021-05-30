#include <iostream>
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
	product(long long _val, int _count) :val(_val), count(_count) {}
};

bool operator<(const product &a, const product &b) // 优先级更弱
{
	if (a.val < b.val)
		return true;
	else if (a.val == b.val)
		if (a.count > b.count)
			return true;

	return false;
}

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
		vector<int> nege_factors; // 负因子
		vector<int> posi_factors; // 正因子

		while (buffer >> temp)
		{
			if (temp > 0)
				posi_factors.push_back(temp); // 正因子
			else if (temp < 0)
				nege_factors.push_back(temp); // 负因子
		}
		// 不考虑只含有0

		sort(posi_factors.begin(), posi_factors.end(), greater<int>()); // 从大到小排序
		sort(nege_factors.begin(), nege_factors.end(), less<int>());    // 从小到大排序

		/* 处理负因子 */
		vector<product> nege_part; // 比较复杂，从大到小乘

		long long sum_nege = 0;   // 负数部分乘积
		int count_nege = 0;    // 负数部分因子数 
		if (nege_factors.size() != 0)
		{
			long long temp = 1;
			for (int i = 0; i < nege_factors.size(); i++)
			{
				temp = temp * nege_factors[i];
				nege_part.push_back(product(temp, i + 1));
			}
			sort(nege_part.begin(), nege_part.end());
			sum_nege = nege_part.back().val;     // 取出最大乘积
			count_nege = nege_part.back().count; // 及其对应个数
		}

		/* 处理正因子 */
		vector<product> posi_part;
		long long sum_posi = 0;   // 正数部分乘积
		int count_posi = 0;    // 正数部分因子数
		if (posi_factors.size() != 0)
		{
			long long temp = 1;
			for (int i = 0; i < posi_factors.size(); i++)
			{
				temp = temp * posi_factors[i];
				posi_part.push_back(product(temp, i + 1));
			}
			sort(posi_part.begin(), posi_part.end());
			sum_posi = posi_part.back().val;     // 取出最大乘积
			count_posi = posi_part.back().count; // 及其对应个数
		}

		long long ans = 0; int min = 0; // ans为满足要求的最大乘积，min为得到该最大积的最少因数个数

		vector<product> result; // 两部分相乘
		result.push_back(product(sum_posi, count_posi));
		result.push_back(product(sum_nege, count_nege));
		result.push_back(product(sum_posi * sum_nege, count_posi + count_nege));
		sort(result.begin(), result.end());
		ans = result.back().val; min = result.back().count;

		if (ans == 0) min = 1;

		cout << " " << ans << " " << min << endl;
	}

	return 0;
}
