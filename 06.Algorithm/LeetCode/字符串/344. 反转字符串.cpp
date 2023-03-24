#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void reverseString(vector<char> &s) 
	{
		for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--) // ����˫ָ��
		{
			swap(s[i], s[j]); // �ܹ�ִ�� n/2 �ν���
		}
	}

	void reverseString2(vector<char> &s) 
	{
		for (int i = 0, j = s.size() - 1; i < j; i++, j--)
		{
			swap(s[i], s[j]);
		}
	}

	// ��ת�ַ���s������ֱյ�����[start, end]
	void reverse(string &s, int start, int end) 
	{
		for (int i = start, j = end; i < j; i++, j--) 
		{
			swap(s[i], s[j]);
		}
	}

	reverse(s, 0, s.size() - 1); // ���ַ���ȫ����ת
};

int main() {
	vector<char> s = { 'H','a','n','n','a','h' };
	Solution solution;
	solution.reverseString(s);
}