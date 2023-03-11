#include <iostream>
using namespace std;

void Solution(int x1, int x2) // 整数根
{
	int a = 1;
	int b = -(x1 + x2);
	int c = x1 * x2;
	printf("%d %d %d\n", a, b, c); // 多组解，两个方程三个未知数，直接令a=1
}

/* Problem D. 数学难题 */
int main()
{
	// 已知一元二次方程的两个整数根，求该一元二次方程。
	// 如有多组解，输出任意一种即可，但要求所有数系数绝对值不超过100000。

	int test_num, a, b; cin >> test_num;
	for (int i = 0; i < test_num; i++)
	{
		cin >> a >> b;
		Solution(a, b);
	}

	return 0;
}
