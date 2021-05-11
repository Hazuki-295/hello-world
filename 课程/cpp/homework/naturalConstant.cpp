#include <iostream>
using namespace std;

void naturalConstant()
{
	double fact = 1, item = 1, sum = 1;
	for (int i = 1; item > pow(10, -15); i++)
	{
		fact = fact * i;
		item = 1 / fact;
		sum = sum + item;
	}
	cout.precision(15);
	cout << "计算的自然常数e为：" << sum << endl;
	cout << "实际的自然常数e为：" << exp(1.0) << endl;

}

int main()
{
	naturalConstant();
	return 0;
}