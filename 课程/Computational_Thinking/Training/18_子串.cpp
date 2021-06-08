#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Solution
{
private:
	string str;         // ������ַ���
	vector<int> cutPoi; // �и�λ��
	vector<string> res; // ��Ž��
public:
	Solution(string s) :str(s) {}

	void cutString(int cutSize) {
		string trim; int cutNum = 0; // �и����
		for (int i = 1; i <= cutSize; i++) { // iΪ�ָ���ʼ��
			trim = str; // ��ԭ
			int index = i;
			while (index <= str.size() + cutPoi.size() - 1) { // �ҳ������и�λ��
				cutPoi.push_back(index);
				index += cutSize + 1;
			}
			for (int i = 0; i < cutPoi.size(); i++) { // ����������
				trim.insert(trim.begin() + cutPoi[i], ' ');
			}
			res.push_back(trim); // ������
			cutPoi.clear();      // ����и�λ��
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
