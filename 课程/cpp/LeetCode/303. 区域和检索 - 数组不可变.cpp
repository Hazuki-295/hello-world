#include <iostream>
#include <vector>
using namespace std;

class NumArray {
public:
	vector<int> sums; 
	// 前缀和数组，sums[i]表示数组nums从下标0到下标i-1的前缀和。sums[0] = 0，无实际意义

	NumArray(vector<int> &nums) {
		int n = nums.size();
		sums.resize(n + 1); 
		// 长度为 n - 1，方便计算 sumRange(i, j)
		for (int i = 0; i < n; i++) {        // 遍历数组 nums 计算前缀和
			sums[i + 1] = sums[i] + nums[i]; // nums[0 ~ i] = nums[0 ~ (i - 1)] + nums[i]
		}
	}

	int sumRange(int i, int j) {      // 每次检索只需要得到两个下标处的前缀和，然后计算差值
		return sums[j + 1] - sums[i]; // sumRange(i, j) = nums[0 ~ j] - nums[0 ~ (i - 1)]
	}
};