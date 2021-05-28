#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
	/* 1.文件重定向。 */
	/* 所需头文件：#include <fstream> */
	ifstream fin("input.txt");   // 已有输入文件
	ofstream fout("output.txt"); // 已有输出文件
	if (!fin) cout << "未找到输入文件：input.txt" << endl;

	streambuf *cinbackup, *coutbackup;
	coutbackup = cout.rdbuf(fout.rdbuf()); // 用rdbuf()重定向
	cinbackup = cin.rdbuf(fin.rdbuf());

	cin.rdbuf(cinbackup);   // 取消，恢复键盘输入
	cout.rdbuf(coutbackup); // 取消，恢复屏幕输出

	/* 2.格式输出控制及其恢复 */
	/* 所需头文件：#include <iomanip> */
	ios init(nullptr);
	init.copyfmt(cout); // 使用copyfmt保存cout的初始格式

	// 格式控制
	cout << setiosflags(ios::left);
	cout << setw(w) << left;

	cout.copyfmt(init); // 格式恢复

	/* 3. */
	/* 所需头文件：#include */

	/* 4. */
	/* 所需头文件：#include */

	return 0;
}
