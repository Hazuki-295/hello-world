#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream fin("input.txt");   // 已有输入文件
	ofstream fout("output.txt"); // 已有输出文件

	// 流缓冲类streambuff，使用该类的成员可以访问到流缓冲区中的数据
	// 定义两个可以用来指向流缓冲区内容的流缓冲指针
	streambuf *cinbackup;
	streambuf *coutbackup;

	/***********************************************************************************
	rdbuf可用来将流重新定义到需要的地方
		streambuf* rdbuf() const;
		streambuf* rdbuf (streambuf* sb);
		1）无参数。返回调用者的流缓冲指针。
		2）参数为流缓冲指针。它使调用者与参数(流缓冲指针)关联，返回自己当前关联的流缓冲区指针。
	***********************************************************************************/

	coutbackup = cout.rdbuf(fout.rdbuf()); // 用rdbuf()重定向
	cinbackup = cin.rdbuf(fin.rdbuf());    // 它将返回自己当前关联的流缓冲区指针

	cout << "write" << endl; // 重定向完成后，使用cout就可以将数据写入对应的文件中

	string line;

	cin >> line; cout << line; // 从input.txt读取数据，写入output.txt

	//restore standard streambuf

	cin.rdbuf(cinbackup);   // 取消，恢复键盘输入
	cout.rdbuf(coutbackup); // 取消，恢复屏幕输出

	return 0;
}
