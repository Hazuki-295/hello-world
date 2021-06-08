#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
private:
	unordered_map<int, bool> vis; // ���ʱ��
	vector<string> res;
public:
	bool match(string x, string y, int resultNum)
	{
		vis.clear(); // ��շ��ʱ��
		if (x.size() != 5) { return false; };
		if (y.size() == 4) y.insert(y.begin(), '0'); // ȱ�0

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
		// ʮ���������0~9���������������λ��(�ɰ���ǰ׺0)
		int x, y; string _x, _y; // ���ӡ���ĸ
		for (y = 1234; (x = y * resultNum) <= 98765; y++) { // ö�ٷ�ĸ
			/* �ж��Ƿ�������� */
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
