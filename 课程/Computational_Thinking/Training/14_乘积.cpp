#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct product { // 乘积
	// 数据成员
	long long val; int start, end, wide; // 乘积、起止范围、范围大小
	// 构造函数
	product(long long val, int start, int end, int wide) :val(val), start(start), end(end), wide(wide) {}
};

bool operator<(const product &a, const product &b) { // 优先级更弱
	if (a.val < b.val)
		return true;
	else if (a.val == b.val)
		if (a.wide > b.wide)
			return true;
		else if (a.wide == b.wide)
			if (a.start > b.start)
				return true;
	return false;
}

/* Problem C. 最大积 */
int main()
{
	// 给定若干个整数S=S1,S2,...,Sn，其中若干个连续数的最大乘积是多少？

	// 最大乘积，因子顺序不变
	string line; int cases = 0;

	while (getline(cin, line)) {
		cout << "Case " << ++cases << ":";
		stringstream buffer(line);

		int temp;
		vector<int> factors; // 因子

		while (buffer >> temp) factors.push_back(temp);

		/* 处理因子 */
		vector<product> result; // 乘积

		int start, end, wide;
		for (int i = 0; i <= factors.size() - 1; i++) { // 枚举求乘积
			temp = factors[i];
			start = i; end = i; wide = end - start;
			result.push_back(product(temp, start, end, wide));
			for (int j = i + 1; j <= factors.size() - 1; j++) {
				temp *= factors[j];
				end = j; wide = end - start;
				result.push_back(product(temp, start, end, wide));
			}
		}

		long long ans = 0; // ans为满足要求的最大乘积及对应的起止范围

		sort(result.begin(), result.end());
		product answer(result.back());
		ans = answer.val; start = answer.start; end = answer.end;

		cout << " " << ans << " " << start << "-" << end << endl;
	}

	return 0;
}
