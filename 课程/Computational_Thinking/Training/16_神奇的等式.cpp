#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
private:
	unordered_map<int, bool> vis; // 访问标记
	vector<string> res;
public:
	bool match(string x, string y, int resultNum)
	{
		vis.clear(); // 清空访问标记
		if (x.size() != 5) { return false; };
		if (y.size() == 4) y.insert(y.begin(), '0'); // 缺项补0

		for (auto c : x) {
			if (vis[c] == true)
				return false;
			else
				vis[c] = true;
		}
		for (auto c : y) {
			if (vis[c] == true)
				return false;
			else
				vis[c] = true;
		}

		string blank(4, ' '), result;
		result = blank + x + "/" + y + "=" + to_string(resultNum);
		res.push_back(result);
		return true;
	}

	void print() {
		for (auto p = res.rbegin(); p != res.rend(); p++)
			cout << *p << endl;
		res.clear();
	}
};

int main()
{
	string line; int cases = 0;
	Solution *obj = new Solution;

	while (getline(cin, line)) {
		cout << "Case " << ++cases << ":" << endl;
		stringstream buffer(line);

		int resultNum; buffer >> resultNum; // 2<=N<=79

		bool find = false;
		// 十个互异的数0~9，分组组成两个五位数(可包含前缀0)
		int x, y; string _x, _y; // 分子、分母
		for (y = 1234; (x = y * resultNum) <= 98765; y++) { // 枚举分母
			/* 判断是否符合条件 */
			if (obj->match(to_string(x), to_string(y), resultNum))
				find = true;
		}

		if (find == false) {
			string blank(4, ' ');
			cout << blank << "No such numbers" << endl;
		}
		else
			obj->print();
	}

	return 0;
}
