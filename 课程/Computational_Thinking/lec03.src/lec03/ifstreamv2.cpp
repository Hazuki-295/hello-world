//使用ifstream和ofstream及cin和cout的rdbuf()
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    printf("   use ifstream/ofstream and cin/cout's rdbuf() function to change console I/O\n");
    //将控制台的标准输入输出改成从文件中读取写入
    ifstream inFile("infile.txt");
    ofstream outFile("outfile.txt");
    //保存原来的输入输出方式 streambuf类就是basic_streambuf类
    streambuf *strmin_buf = cin.rdbuf();
    streambuf *strmout_buf = cout.rdbuf();
    printf("Begin to read/write file\n....\n");
    //重定向到文件
    cin.rdbuf(inFile.rdbuf());
    cout.rdbuf(outFile.rdbuf());
    //原程序代码
    int n;
    while (cin >> n)
    {
        n *= 2;
        cout << n << endl;
    }
    inFile.close();
    outFile.close();
    //回到控制台的标准输入输出
    cin.rdbuf(strmin_buf);
    cout.rdbuf(strmout_buf);
    cout << "Finished processing, read from console(0 to exit):" << endl;
    do
    {
        cin >> n;
        cout << 2 * n << endl;
    } while (n != 0);
    return 0;
}