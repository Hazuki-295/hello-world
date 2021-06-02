#include <iostream>
#include <vector>
using namespace std;

/* 쳲��������У���0��1��ʼ�������ÿһ�����ֶ���ǰ���������ֵĺ͡� */
class Solution {
public:
	int fib(int n) {
		if (n <= 1)
			return n;
		vector<int> dp(n + 1); // dp[i]�Ķ���Ϊ����i������쳲�������ֵ��dp[i]
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= n; i++) {     // n>1
			dp[i] = dp[i - 1] + dp[i - 2]; // ״̬ת�Ʒ���(���ƹ�ϵ)
		}
		return dp[n];
	}
};

/* �������飬���Ϳռ临�Ӷ� */
class Solution {
public:
	int fib(int n) {
		if (n <= 1)
			return n;
		int dp[2], sum;
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= n; i++) // ��һ�μ���dp[2]
		{
			sum = dp[0] + dp[1];
			dp[0] = dp[1];
			dp[1] = sum;
		}
		return dp[1];
	}
};

/* �ݹ�ⷨ */
class Solution {
public:
	int fib(int n) {
		if (n <= 1) return n;
		return fib(n - 1) + fib(n - 2);
	}
};