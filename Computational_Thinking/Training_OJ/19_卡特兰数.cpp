#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution
{
private:
	unordered_set<string> res; int length;
public:
	// 从A串的第一个字符开始，依次取出串中的每个字符
	// 可以选择将取出的字符直接放入字符串B或C的尾部
	// 若字符串A或B中还有字符，
	// 可以继续从A中按顺序取出单个字符放入串B或C的尾部，
	// 也可以选择从串B的尾部取出单个字符并放入串C的尾部
	Solution(int length) :length(length) {}

	void backtrack(string &A, string &B, string &C) {
		if (A.size() == 0 && B.size() == 0) { // 所有字符都放入C了
			res.insert(C); // 得到一个等价串
			return;
		}

		if (B.size() != 0) {
			char temp = B.back();
			B.pop_back(); C.push_back(temp); // 尝试
			backtrack(A, B, C);
			B.push_back(temp); C.pop_back(); // 回溯
		}

		if (A.size() != 0) {
			char temp = A.front(); A.erase(A.begin());
			B.push_back(temp); backtrack(A, B, C); B.pop_back(); // 尝试并回溯
			C.push_back(temp); backtrack(A, B, C); C.pop_back(); // 尝试并回溯
			A.insert(A.begin(), temp);
		}
	}

	bool exsit(string &s) {
		return find(res.begin(), res.end(), s) != res.end();
	}
};

int main()
{
	int cases = 0; string str, s;
	while (cin >> str >> s) {
		cout << "Case " << ++cases << ": ";
		Solution *obj = new Solution(str.length());
		string B, C; obj->backtrack(str, B, C);

		if (obj->exsit(s))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}
