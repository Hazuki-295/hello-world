#include <iostream>
#include <algorithm>
using namespace std;

/* 辗转相除法，求两个正整数 m 和 n 的最大公约数 */
int gcd(int m, int n)
{
	// 记两个正整数a,b的最大公因数为gcd(a,b)，反复执行操作gcd(a,b)→gcd(b,r)，
	// 其中r=a mod b，直到r=0，停止操作，此时得到的b，就是最大公因数。
	int a = m, b = n; if (m < n) swap(a, b); // a>b
	int r = b;

	while (r != 0) {
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

/* Problem E. 优美的GCD */
int main()
{
	int test_num, a, b; cin >> test_num;
	for (int i = 0; i < test_num; i++)
	{
		cin >> a >> b;
		cout << gcd(a, b) << endl;
	}

	return 0;
}
