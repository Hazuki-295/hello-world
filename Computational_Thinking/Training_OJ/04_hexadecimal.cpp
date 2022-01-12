#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

/* (带符号整数)十六进制转十进制 */
int HexToDec(string hex) {
	int sum = 0, temp; bool negative = false;
	int prefix = 2; // 前缀符号数
	if (hex[0] == '-') { // 负数
		negative = true;
		prefix = 3; // "-0x"
	}
	int exp = (hex.size() - prefix) - 1; // n位数，指数为0,1,2,...,n-1
	for (auto c = hex.begin() + prefix; c != hex.end(); c++) { // 跳过0x
		if (isdigit(*c))
			temp = *c - '0';
		else if (*c >= 'a' && *c <= 'f')
			temp = *c - 'a' + 10;
		else
			temp = *c - 'A' + 10;
		sum = sum + temp * pow(16, exp);
		exp--;
	}
	if (negative)
		sum *= -1;
	return sum;
}

int main() {
	string line; stringstream buffer;

	while (getline(cin, line)) { // 对一整行十六进制数求和
		// int hex_num;
		string hex;                 // 创建一个保存一个十六进制数的string对象
		istringstream buffer(line); // 将buffer绑定到刚读入的行

		int sum = 0;
		// while (buffer >> hex >> hex_num) // 读取十六进制数
			// sum = sum + hex_num;
		while (buffer >> hex) // 读取十六进制数
			sum = sum + HexToDec(hex);
		cout << sum << endl;
	}

	return 0;
}
