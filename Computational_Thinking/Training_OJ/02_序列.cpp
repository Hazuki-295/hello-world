#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

/* 给你一个整数n，请你找出并返回第n个丑数 */
size_t nthUglyNumber(int n) {
	vector<int> factors = { 2, 3, 5 }; // 只含有因子2,3,5
	unordered_set<size_t> seen;          // 为了避免重复元素，使用哈希集合去重，避免相同元素多次加入堆
	priority_queue<size_t, vector<size_t>, greater<size_t>> heap; // 最小堆(默认基于vector实现)，从大到小排序

	seen.insert(1L);
	heap.push(1L);   // 将最小的丑数1加入堆
	size_t ugly = 0;
	for (int i = 0; i < n; i++) {
		size_t curr = heap.top(); // 每次取出堆顶元素x，则x是堆中"最小的丑数"
		heap.pop();

		ugly = curr; // 第n次从最小堆中取出的元素即为第n个丑数

		for (int factor : factors) { // 由于2x,3x,5x也是丑数，因此将2x,3x,5x加入堆 
			size_t next = curr * factor;
			if (!seen.count(next)) { // 未重复，没有加入过最小堆
				seen.insert(next); // 去重
				heap.push(next);   // 加入最小堆
			}
		}
	}
	return ugly;
}

/* 给你一个整数n，请你找出并返回第n个丑数 */
size_t nthUglyNumber2(int n) {
	vector<size_t> dp(n + 1); // 0号元素未用
	dp[1] = 1; // 最小的丑数1
	int p2 = 1, p3 = 1, p5 = 1;  // 指数，只含有因子2,3,5
	for (int i = 2; i <= n; i++) {
		size_t num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5; // 动态规划
		dp[i] = min(min(num2, num3), num5); // 每次加入一个数
		if (dp[i] == num2) p2++;
		if (dp[i] == num3) p3++;
		if (dp[i] == num5) p5++;
	}
	return dp[n];
}


int main() {
	int n;
	while (cin >> n) {
		cout << nthUglyNumber(n) << endl;
	}
		
}
