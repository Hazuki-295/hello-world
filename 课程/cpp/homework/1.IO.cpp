#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main() {
	vector<int> nums; nums.resize(4);
	cout << "������4��������" << endl;
	int tmp;
	for (int i = 0; i < nums.size(); i++) {
		cin >> tmp;
		nums[i] = tmp;
	}

	string source = "d:\\source.txt";
	string destination = "d:\\destination.txt";

	// �Ӽ�������10��20��30��40�ĸ��������롰d:\\source.txt���ļ���
	ofstream out(source);
	for (auto x : nums) {
		out << x << " ";
	}
	out.close();

	// Ȼ�󣬶����⼸�����֣��������Ǳ��101��202��303��404�����롱d:\\destination.txt���С�
	ifstream in(source);
	out.open(destination);
	for (int i = 0; i < nums.size(); i++) {
		in >> tmp;
		out << tmp * 10.1 << " ";
	}
	in.close(); out.close();
}
