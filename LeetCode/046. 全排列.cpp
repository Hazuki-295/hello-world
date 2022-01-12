#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
private:
	unordered_map<int, bool> vis; // 访问标记
	vector<int> output; // 存放得到的一个排列
public:
	/* 回溯法，一种通过探索所有可能的候选解来找出所有的解的算法。 */
	void backtrack(vector<vector<int>> &res, vector<int> &nums) {
		if (output.size() == nums.size()) { // 所有数都填完了
			res.emplace_back(output); // 得到一个排列的结果
			return;
		}

		// 如果候选解被确认不是一个解（或者至少不是最后一个解），回溯算法会通过在上一步进行一些变化抛弃该解，即回溯并且再次尝试
		for (int i = 0; i < nums.size(); i++) { // 逐一枚举，选择一个数
		
			if (vis[nums[i]]) continue; // 使用过的元素，直接跳过

			output.push_back(nums[i]); vis[nums[i]] = true; // 使用该元素
			backtrack(res, nums); // 向下递归填下一个数
			output.pop_back(); vis[nums[i]] = false; // 回溯，撤销操作(状态重置)
			// 深度优先遍历在回到上一层结点时需"状态重置"。正是由于回到了之前的状态，才可以开始下一个选择的尝试。
		}
	}

	vector<vector<int>> permute(vector<int> &nums) {
		vector<vector<int>> res; // 存放全排列的结果
		vis.clear();             // 清空访问标记
		backtrack(res, nums);    // 回溯法得到全排列(按字典序顺序)
		return res;
	}
};

int main()
{
	vector<int> nums;
	for (int i = 0; i <= 9; i++) { // 初始为{0,1,2,3,4 | 5,6,7,8,9}
		nums.push_back(i);
	}
	Solution *obj = new Solution;
	vector<vector<int>> result(obj->permute(nums));
	return 0;
}