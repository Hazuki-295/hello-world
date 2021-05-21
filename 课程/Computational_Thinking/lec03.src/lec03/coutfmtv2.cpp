#include <iostream>
using namespace std;
int main()
{
    int a = 21;
    cout.setf(ios::showbase); //设置输出时的基数符号
    cout << "dec:" << a << endl;
    cout.unsetf(ios::dec); //终止十进制的格式设置
    cout.setf(ios::hex);   //设置以十六进制输出的状态
    cout << "hex:" << a << endl;
    cout.unsetf(ios::hex); //终止十六进制的格式设置
    cout.setf(ios::oct);   //设置以八进制输出的状态
    cout << "oct:" << a << endl;
    cout.unsetf(ios::oct); //终止以八进制的输出格式设置
    char *pt = "China";    //pt指向字符串”china”
    cout.width(10);        //指定域宽为10
    cout << pt << endl;
    cout.width(10); //指定域宽为10
    cout.fill('*'); //指定空白处以'*'填充
    cout << pt << endl;
    double pi = 22.0 / 7.0;     //计算pi值
    cout.setf(ios::scientific); //指定用科学记数法输出
    cout << "pi=";              //输出"pi="
    cout.width(14);             //指定域宽为14
    cout << pi << endl;
    cout.unsetf(ios::scientific); //终止科学记数法状态
    cout.setf(ios::fixed);        //指定用定点形式输出
    cout.width(12);               //指定域宽为12
    cout.setf(ios::showpos);      //在输出正数时显示“+”号
    cout.setf(ios::internal);     //数符出现在左侧
    cout.precision(6);            //保留6位小数
    cout << pi << endl;
    return 0;
}
