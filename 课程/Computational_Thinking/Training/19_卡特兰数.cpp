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
	// ��A���ĵ�һ���ַ���ʼ������ȡ�����е�ÿ���ַ�
	// ����ѡ��ȡ�����ַ�ֱ�ӷ����ַ���B��C��β��
	// ���ַ���A��B�л����ַ���
	// ���Լ�����A�а�˳��ȡ�������ַ����봮B��C��β����
	// Ҳ����ѡ��Ӵ�B��β��ȡ�������ַ������봮C��β��
	Solution(int length) :length(length) {}

	void backtrack(string &A, string &B, string &C) {
		if (C.size() == length) { // �����ַ�������C��
			res.push_back(C); // �õ�һ���ȼ۴�
			return;
		}

		if (A.size() + B.size() + C.size() != length) return;

		string copy_A(A), copy_B(B), copy_C(C);
		if (B.size() != 0) {
			char temp = B.back();
			B.pop_back(); C.push_back(temp);    // ����
			backtrack(A, B, C);
			A = copy_A; B = copy_B; C = copy_C; // ����
		}

		if (A.size() != 0) {
			char temp = A.front(); A.erase(A.begin());
			B.push_back(temp); backtrack(A, B, C);  // ����
			A = copy_A; B = copy_B; C = copy_C;     // ����
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
