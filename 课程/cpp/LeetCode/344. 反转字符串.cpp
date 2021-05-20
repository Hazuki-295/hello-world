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
};

int main() {
	vector<char> s = { 'H','a','n','n','a','h' };
	Solution solution;
	solution.reverseString(s);
}