#include <iostream>
using namespace std;

/* 输出 底边长为n 的实心等腰三角形 */
void printTriangle(char c, int n) {
	int blankNum = n - 1;
	for (int line = 1; line <= n; line++) {
		cout << string(blankNum, ' ');
		for (int i = 1; i <= line - 1; i++) {
			cout << c << " ";
		}
		cout << c;
		cout << string(blankNum, ' ') << endl;
		blankNum--;
	}
}

/* 输出 底边长为n 的镂空等腰三角形 */
void printTriangle2(char c, int n) {
	int blankNum = n - 1;
	for (int line = 1; line <= n; line++) { // 打印n行
		cout << string(blankNum, ' ');
		for (int i = 1; i <= line - 1; i++) {
			if (line != n) { // 如果不是最后一行，镂空三角型

				if (i == 1)
					cout << c << " ";
				else
					cout << ' ' << " ";
			}
			else if (line == n) // 如果是最后一行，实心三角型
				cout << c << " ";
		}
		cout << c;
		cout << string(blankNum, ' ') << endl;
		blankNum--;
	}
}

int main() {
	char c; int n;
	cin >> c >> n;
	printTriangle(c, n);
	return 0;
}