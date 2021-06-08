#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution
{
private:
	vector<string> res; int length;
public:
	// 从A串的第一个字符开始，依次取出串中的每个字符
	// 可以选择将取出的字符直接放入字符串B或C的尾部
	// 若字符串A或B中还有字符，
	// 可以继续从A中按顺序取出单个字符放入串B或C的尾部，
	// 也可以选择从串B的尾部取出单个字符并放入串C的尾部
	Solution(int length) :length(length) {}

	void backtrack(string &A, string &B, string &C) {
		if (C.size() == length) { // 所有字符都放入C了
			res.push_back(C); // 得到一个等价串
			return;
		}

		if (A.size() + B.size() + C.size() != length) return;

		string copy_A(A), copy_B(B), copy_C(C);
		if (B.size() != 0) {
			char temp = B.back();
			B.pop_back(); C.push_back(temp);    // 尝试
			backtrack(A, B, C);
			A = copy_A; B = copy_B; C = copy_C; // 回溯
		}

		if (A.size() != 0) {
			char temp = A.front(); A.erase(A.begin());
			B.push_back(temp); backtrack(A, B, C);  // 尝试
			A = copy_A; B = copy_B; C = copy_C;     // 回溯
			C.push_back(temp); backtrack(A, B, C);
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
