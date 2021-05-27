#include <iostream>
#include <algorithm>
using namespace std;

/* 辗转相除法 */
int gcd(int m, int n)
{
	int a, b, r;
	m > n ? (a = m, b = n) : (a = n, b = m);

	a = m, b = n, r = b;  // a>b

	int count = 0;

	while (r != 0)
	{
		r = a % b; count++;
		a = b;
		b = r;
	}
	return count;
}

/* Problem E. 优美的GCD */
int main()
{
	int T, a, b; cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> a >> b;
		cout << gcd(a, b) << endl;
	}
}