#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string line; int cases = 0;

	while (getline(cin, line)) {
		cout << "Case " << ++cases << ":" << endl;
		stringstream buffer(line);

		int x, maxRange; buffer >> x >> maxRange;

		bool find = false;
		int a, b, c, d; // ö�١�Լ��������1<=a<=b<=c<=d<=maxRange
		for (a = 1; a <= maxRange; a++) {
			for (b = a; b <= maxRange; b++) {
				for (c = b; c <= maxRange; c++) {
					for (d = c; d <= maxRange; d++) {
						if ((size_t)(pow(a, x) + pow(b, x) + pow(c, x)) == (size_t)pow(d, x)) {
							printf("%d^%d+%d^%d+%d^%d=%d^%d\n", a, x, b, x, c, x, d, x);
							// ����a,b,c����Ȼ������������
							if (find == false) find = true;
						}
					}
				}
			}
		}
		if (find == false) cout << "No such numbers." << endl;
	}

	return 0;
}
