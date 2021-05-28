#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

/* 给你一个整数n，请你找出并返回第n个丑数 */
class Solution {
public:
	int nthUglyNumber(int n)
	{
		vector<int> factors = { 2, 3, 5 }; // 只含有因子2,3,5
		unordered_set<long> seen;          // 为了避免重复元素，使用哈希集合去重，避免相同元素多次加入堆
		priority_queue<long, vector<long>, greater<long>> heap; // 最小堆(默认基于vector实现)，从大到小排序

		seen.insert(1L);
		heap.push(1L);   // 将最小的丑数1加入堆
		int ugly = 0;
		for (int i = 0; i < n; i++)
		{
			long curr = heap.top(); // 每次取出堆顶元素x，则x是堆中"最小的丑数"
			heap.pop();

			ugly = (int)curr; // 第n次从最小堆中取出的元素即为第n个丑数

			for (int factor : factors) // 由于2x,3x,5x也是丑数，因此将2x,3x,5x加入堆
			{
				long next = curr * factor;
				if (!seen.count(next)) // 未重复，没有加入过最小堆
				{
					seen.insert(next); // 去重
					heap.push(next);   // 加入最小堆
				}
			}
		}
		return ugly;
	}
};
