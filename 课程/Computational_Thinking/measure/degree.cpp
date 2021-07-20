#include <iostream>
using namespace std;

class Degree {
public:
	int degree; // 度
	int minute; // 分
	int second; // 秒
public:
	// 构造函数
	Degree() = default;
	Degree(int degree, int minute, int second) :degree(degree), minute(minute), second(second) {}
};

Degree operator-(Degree &a, Degree &b) {
	int second_a = a.degree * 60 * 60 + a.minute * 60 + a.second;
	int second_b = b.degree * 60 * 60 + b.minute * 60 + b.second;
	if (second_a < second_b) {
		second_a += 360 * 60 * 60;
	}
	int second = second_a - second_b;

	int degree = second / 3600;
	second %= 3600;
	int minute = second / 60;
	second %= 60;
	return Degree(degree, minute, second);
}

Degree average(Degree &a, Degree &b) {
	int second_a = a.degree * 60 * 60 + a.minute * 60 + a.second;
	int second_b = b.degree * 60 * 60 + b.minute * 60 + b.second;
	int second = (second_a + second_b) / 2;

	int degree = second / 3600;
	second %= 3600;
	int minute = second / 60;
	second %= 60;
	return Degree(degree, minute, second);
}

istream &operator>>(istream &is, Degree &temp)
{
	is >> temp.degree >> temp.minute >> temp.second;
	return is;
}

ostream &operator<<(ostream &os, const Degree &temp)
{
	os << temp.degree << ' ' << temp.minute << ' ' << temp.second;
	return os;
}

void process(Degree pleft_leftobj, Degree pleft_rightobj, Degree pright_rightobj, Degree pright_leftobj) {
	Degree pleft = pleft_rightobj - pleft_leftobj;    // 右目标读数 - 左目标读数
	Degree pright = pright_rightobj - pright_leftobj;
	cout << "测试检验：左目标 " << pleft_leftobj - pright_leftobj;
	cout << "，右目标 " << pleft_rightobj - pright_rightobj << endl;
	cout << "半测回角值（盘左）= " << pleft << endl;
	cout << "半测回角值（盘右）= " << pright << endl;
	cout << "一测回平均角值 = " << average(pleft, pright) << endl;
}

int main() {
	Degree pleft_leftobj, pleft_rightobj, pright_rightobj, pright_leftobj;
	while (true) {
		cout << "请输入数据：" << endl;
		cin >> pleft_leftobj >> pleft_rightobj >> pright_rightobj >> pright_leftobj;
		process(pleft_leftobj, pleft_rightobj, pright_rightobj, pright_leftobj);
		cout << endl;
	}
}
