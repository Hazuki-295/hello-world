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
		// ʮ���������0~9���������������λ��(�ɰ���ǰ׺0)
		// ���е��������



		if (find == false)
			cout << "No such numbers." << endl;
	}

	return 0;
}
