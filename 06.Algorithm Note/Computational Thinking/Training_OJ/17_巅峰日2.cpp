#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int cases = 0, d; // 计算的开始时间
	vector<int> period; period.resize(4);     // 周期
	vector<int> firstday; firstday.resize(4); // 在一年中第一次达到高峰的时间

	while (cin >> period[0] >> period[1] >> period[2] >> period[3] >> firstday[0] >> firstday[1] >> firstday[2] >> firstday[3] >> d) {
		cout << "Case " << ++cases << ": ";

		int product = 1; // 周期之积
		for (int i = 0; i < 4; i++) { product *= period[i]; }
		int maxRange = product + 365; // 周期之积后一年

		bool find = false; int res; // 结果
		for (int i = d + 1; i <= maxRange; i++) { // 逐一枚举
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
