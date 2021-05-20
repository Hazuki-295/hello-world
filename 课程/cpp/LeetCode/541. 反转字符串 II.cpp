#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	string reverseStr(string s, int k) // ���ַ�����ͷ����ÿ�� 2k ���ַ���ǰ k ���ַ����з�ת
	{
		for (int i = 0; i < s.size(); i += (2 * k)) // ÿ�δ��������СΪ2k���ַ���i+=2k�����������
		{
			
			// 1. ʣ���ַ�С�� 2k �����ڻ���� k ������תǰ k ���ַ�
			if (i + k <= s.size()) // �д�СΪk�ķ�ת����
			{
				reverse(s.begin() + i, s.begin() + i + k); // ��ת�����ڵ�Ԫ��
				continue; // δ����β
			}
			// 2. ʣ���ַ����� k ������ʣ���ַ�ȫ����ת��
			reverse(s.begin() + i, s.begin() + s.size());
		}
		return s;
	}
};

int main() {
	string s("abcdefg"); int k = 2;
	Solution solution;
	cout << solution.reverseStr(s, k) << endl;
}