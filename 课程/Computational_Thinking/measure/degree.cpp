#include <iostream>
using namespace std;

class Degree {
public:
	int degree; // ��
	int minute; // ��
	int second; // ��
public:
	// ���캯��
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
	Degree pleft = pleft_rightobj - pleft_leftobj;    // ��Ŀ����� - ��Ŀ�����
	Degree pright = pright_rightobj - pright_leftobj;
	cout << "���Լ��飺��Ŀ�� " << pleft_leftobj - pright_leftobj;
	cout << "����Ŀ�� " << pleft_rightobj - pright_rightobj << endl;
	cout << "���ؽ�ֵ������= " << pleft << endl;
	cout << "���ؽ�ֵ�����ң�= " << pright << endl;
	cout << "һ���ƽ����ֵ = " << average(pleft, pright) << endl;
}

int main() {
	Degree pleft_leftobj, pleft_rightobj, pright_rightobj, pright_leftobj;
	while (true) {
		cout << "���������ݣ�" << endl;
		cin >> pleft_leftobj >> pleft_rightobj >> pright_rightobj >> pright_leftobj;
		process(pleft_leftobj, pleft_rightobj, pright_rightobj, pright_leftobj);
		cout << endl;
	}
}
