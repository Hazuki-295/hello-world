#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct attribute
{
	// ���ݳ�Ա
	int period;   // ����
	int firstday; // ��һ���е�һ�δﵽ�߷��ʱ��
	int day;      // ��ǰ�ۼƵ�����
	// ���캯��
	attribute(int period, int firstday) :period(period), firstday(firstday), day(firstday) {}
};

bool operator<(const attribute &a, const attribute &b) { return a.day < b.day; }

int main()
{
	// ÿһ�������л���һ���Ǹ߷�
	string line1, line2; int cases = 0;

	while (getline(cin, line1) && getline(cin, line2)) {
		cout << "Case " << ++cases << ": ";
		stringstream buffer1(line1), buffer2(line2);

		int product = 1; // ����֮��
		vector<int> period; period.resize(4);     // ����
		vector<int> firstday; firstday.resize(5); // ��һ���е�һ�δﵽ�߷��ʱ��
		for (int i = 0; i < 4; i++) {
			buffer1 >> period[i];
			product *= period[i];
		}
		int maxRange = product + 365; // ����֮����һ��

		for (int i = 0; i < 5; i++)
			buffer2 >> firstday[i];
		int d = firstday.back(); // ��ʼ����

		vector<attribute> attributes;
		for (int i = 0; i < 4; i++) {
			attributes.push_back(attribute(period[i], firstday[i]));
			while (attributes[i].day < d)
				attributes[i].day += attributes[i].period; // ���ٱ�dҪ��
		}

		bool find = false; int res; // ���
		sort(attributes.begin(), attributes.end());
		while (true)
		{
			attributes[0].day += attributes[0].period;
			sort(attributes.begin(), attributes.end());

			if (attributes[3].day == attributes[0].day) {
				find = true;
				res = attributes[0].day - d; // ��һ���۷��վ����������d������
				break;
			}
			else if (attributes[3].day > maxRange)
				break;
		}

		if (find)
			cout << res << endl;
		else
			cout << "No such days." << endl;
	}

	return 0;
}
