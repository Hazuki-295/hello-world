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
	// ��A���ĵ�һ���ַ���ʼ������ȡ�����е�ÿ���ַ�
	// ����ѡ��ȡ�����ַ�ֱ�ӷ����ַ���B��C��β��
	// ���ַ���A��B�л����ַ���
	// ���Լ�����A�а�˳��ȡ�������ַ����봮B��C��β����
	// Ҳ����ѡ��Ӵ�B��β��ȡ�������ַ������봮C��β��
	Solution(int length) :length(length) {}

	void backtrack(string &A, string &B, string &C) {
		if (A.size() == 0 && B.size() == 0) { // �����ַ�������C��
			res.insert(C); // �õ�һ���ȼ۴�
			return;
		}

		if (B.size() != 0) {
			char temp = B.back();
			B.pop_back(); C.push_back(temp); // ����
			backtrack(A, B, C);
			B.push_back(temp); C.pop_back(); // ����
		}

		if (A.size() != 0) {
			char temp = A.front(); A.erase(A.begin());
			B.push_back(temp); backtrack(A, B, C); B.pop_back(); // ���Բ�����
			C.push_back(temp); backtrack(A, B, C); C.pop_back(); // ���Բ�����
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
