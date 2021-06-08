#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int cases = 0, d; // ����Ŀ�ʼʱ��
	vector<int> period; period.resize(4);     // ����
	vector<int> firstday; firstday.resize(4); // ��һ���е�һ�δﵽ�߷��ʱ��

	while (cin >> period[0] >> period[1] >> period[2] >> period[3] >> firstday[0] >> firstday[1] >> firstday[2] >> firstday[3] >> d) {
		cout << "Case " << ++cases << ": ";

		int product = 1; // ����֮��
		for (int i = 0; i < 4; i++) { product *= period[i]; }
		int maxRange = product + 365; // ����֮����һ��

		bool find = false; int res; // ���
		for (int i = d + 1; i <= maxRange; i++) { // ��һö��
			bool match = true;
			for (int j = 0; j < 4; j++) {
				if ((i - firstday[j]) % period[j] != 0) {
					match = false;
					break;
				}
			}
			if (match == true) {
				res = i - d; find = true;
				break;
			}
		}

		if (find)
			cout << res << endl;
		else
			cout << "No such days." << endl;
	}

	return 0;
}
