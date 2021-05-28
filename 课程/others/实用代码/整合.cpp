#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream fin("input.txt");   // 已有输入文件
	if (!fin) cout << "未找到输入文件：input.txt" << endl;
	ofstream fout("output.txt"); // 已有输出文件
	streambuf *cinbackup, *coutbackup;
	coutbackup = cout.rdbuf(fout.rdbuf()); // 用rdbuf()重定向
	cinbackup = cin.rdbuf(fin.rdbuf());

	//restore standard streambuf
	cin.rdbuf(cinbackup);   // 取消，恢复键盘输入
	cout.rdbuf(coutbackup); // 取消，恢复屏幕输出

	return 0;
}
