#include <iostream>
using namespace std;

int main() {
	double forward, back;
	while (true) {
		cout << "������������ݣ�" << endl;
		cout << "���⣺"; cin >> forward;
		cout << "���⣺"; cin >> back;
		double average = (forward + back) / 2;
		cout << "��Խϲ� = 1/" << (int)(average / abs(forward - back)) << endl << endl;
	}
}
