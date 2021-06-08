#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string line; int cases = 0;

	while (getline(cin, line)) {
		cout << "Case " << ++cases << ":" << endl;
		stringstream buffer(line); string blank(4, ' ');

		int resultNum; buffer >> resultNum;

		bool find = false;
		// 十个互异的数0~9，分组组成两个五位数(可包含前缀0)
		// 所有的排列组合



		if (find == false)
			cout << "No such numbers." << endl;
	}

	return 0;
}
