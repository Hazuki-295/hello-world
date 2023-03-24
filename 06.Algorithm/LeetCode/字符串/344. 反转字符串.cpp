#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void reverseString(vector<char> &s) 
	{
		for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--) // 定义双指针
		{
			swap(s[i], s[j]); // 总共执行 n/2 次交换
		}
	}

	void reverseString2(vector<char> &s) 
	{
		for (int i = 0, j = s.size() - 1; i < j; i++, j--)
		{
			swap(s[i], s[j]);
		}
	}

	// 反转字符串s中左闭又闭的区间[start, end]
	void reverse(string &s, int start, int end) 
	{
		for (int i = start, j = end; i < j; i++, j--) 
		{
			swap(s[i], s[j]);
		}
	}

	reverse(s, 0, s.size() - 1); // 将字符串全部反转
};

int main() {
	vector<char> s = { 'H','a','n','n','a','h' };
	Solution solution;
	solution.reverseString(s);
}