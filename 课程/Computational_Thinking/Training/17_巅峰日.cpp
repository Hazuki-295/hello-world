#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct attribute
{
	// 数据成员
	int period;   // 周期
	int firstday; // 在一年中第一次达到高峰的时间
	int day;      // 当前累计的天数
	// 构造函数
	attribute(int period, int firstday) :period(period), firstday(firstday), day(firstday) {}
};

bool operator<(const attribute &a, const attribute &b) { return a.day < b.day; }

int main()
{
	// 每一个周期中会有一天是高峰
	string line1, line2; int cases = 0;

	while (getline(cin, line1) && getline(cin, line2)) {
		cout << "Case " << ++cases << ": ";
		stringstream buffer1(line1), buffer2(line2);

		int product = 1; // 周期之积
		vector<int> period; period.resize(4);     // 周期
		vector<int> firstday; firstday.resize(5); // 在一年中第一次达到高峰的时间
		for (int i = 0; i < 4; i++) {
			buffer1 >> period[i];
			product *= period[i];
		}
		int maxRange = product + 365; // 周期之积后一年

		for (int i = 0; i < 5; i++)
			buffer2 >> firstday[i];
		int d = firstday.back(); // 开始日期

		vector<attribute> attributes;
		for (int i = 0; i < 4; i++) {
			attributes.push_back(attribute(period[i], firstday[i]));
			while (attributes[i].day < d)
				attributes[i].day += attributes[i].period; // 至少比d要大
		}

		bool find = false; int res; // 结果
		sort(attributes.begin(), attributes.end());
		while (true)
		{
			attributes[0].day += attributes[0].period;
			sort(attributes.begin(), attributes.end());

			if (attributes[3].day == attributes[0].day) {
				find = true;
				res = attributes[0].day - d; // 第一个巅峰日距离给定日期d的天数
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
