#include <iostream>
using namespace std;

int main() {
	double forward, back;
	while (true) {
		cout << "请输入测量数据：" << endl;
		cout << "往测："; cin >> forward;
		cout << "返测："; cin >> back;
		double average = (forward + back) / 2;
		cout << "相对较差 = 1/" << (int)(average / abs(forward - back)) << endl << endl;
	}
}
