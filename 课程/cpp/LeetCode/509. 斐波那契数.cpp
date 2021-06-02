#include <iostream>
#include <vector>
using namespace std;

/* 斐波那契数列，由0和1开始，后面的每一项数字都是前面两项数字的和。 */
class Solution {
public:
	int fib(int n) {
		if (n <= 1)
			return n;
		vector<int> dp(n + 1); // dp[i]的定义为：第i个数的斐波那契数值是dp[i]
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= n; i++) {     // n>1
			dp[i] = dp[i - 1] + dp[i - 2]; // 状态转移方程(递推关系)
		}
		return dp[n];
	}
};

/* 滚动数组，降低空间复杂度 */
class Solution {
public:
	int fib(int n) {
		if (n <= 1)
			return n;
		int dp[2], sum;
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= n; i++) // 第一次计算dp[2]
		{
			sum = dp[0] + dp[1];
			dp[0] = dp[1];
			dp[1] = sum;
		}
		return dp[1];
	}
};

/* 递归解法 */
class Solution {
public:
	int fib(int n) {
		if (n <= 1) return n;
		return fib(n - 1) + fib(n - 2);
	}
};