#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Solution
{
private:
	string str;         // 处理的字符串
	vector<int> cutPoi; // 切割位置
	vector<string> res; // 存放结果
public:
	Solution(string s) :str(s) {}

	void cutString(int cutSize) {
		string trim; int cutNum = 0; // 切割个数
		for (int i = 1; i <= cutSize; i++) { // i为分割起始点
			trim = str; // 复原
			int index = i;
			while (index <= str.size() + cutPoi.size() - 1) { // 找出所有切割位置
				cutPoi.push_back(index);
				index += cutSize + 1;
			}
			for (int i = 0; i < cutPoi.size(); i++) { // 真正地修饰
				trim.insert(trim.begin() + cutPoi[i], ' ');
			}
			res.push_back(trim); // 加入结果
			cutPoi.clear();      // 清空切割位置
		}
		for (auto x : res)
			cout << x << endl;
		res.clear();
	}
};

int main()
{
	int cases = 0, cutSize;
	string str; cin >> str;
	Solution *obj = new Solution(str);
	while (cin >> cutSize) {
		cout << "Case " << ++cases << ":" << endl;
		obj->cutString(cutSize);
	}

	return 0;
}
