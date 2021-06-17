#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main() {
	vector<int> nums; nums.resize(4);
	cout << "请输入4个整数。" << endl;
	int tmp;
	for (int i = 0; i < nums.size(); i++) {
		cin >> tmp;
		nums[i] = tmp;
	}

	string source = "d:\\source.txt";
	string destination = "d:\\destination.txt";

	// 从键盘输入10，20，30，40四个数，存入“d:\\source.txt”文件中
	ofstream out(source);
	for (auto x : nums) {
		out << x << " ";
	}
	out.close();

	// 然后，读出这几个数字，并把它们变成101，202，303，404，存入”d:\\destination.txt”中。
	ifstream in(source);
	out.open(destination);
	for (int i = 0; i < nums.size(); i++) {
		in >> tmp;
		out << tmp * 10.1 << " ";
	}
	in.close(); out.close();
}
