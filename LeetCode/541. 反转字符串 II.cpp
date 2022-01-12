#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	string reverseStr(string s, int k) // 从字符串开头算起，每隔 2k 个字符的前 k 个字符进行反转
	{
		for (int i = 0; i < s.size(); i += (2 * k)) // 每次处理区间大小为2k的字符，i+=2k计算区间起点
		{
			
			// 1. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
			if (i + k <= s.size()) // 有大小为k的翻转区间
			{
				reverse(s.begin() + i, s.begin() + i + k); // 翻转区间内的元素
				continue; // 未到结尾
			}
			// 2. 剩余字符少于 k 个，则将剩余字符全部反转。
			reverse(s.begin() + i, s.begin() + s.size());
		}
		return s;
	}
};

int main() {
	string s("abcdefg"); int k = 2;
	Solution solution;
	cout << solution.reverseStr(s, k) << endl;
}