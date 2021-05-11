#include <iostream>
using namespace std;

int LotteryNum(int n, int k)
{
	int num, case1, case2;
	if (n == k || k == 0) // ��
		num = 1;
	else // C(n,k) = C(n-1,k-1) + C(n-1,k)
	{
		case1 = LotteryNum(n - 1, k - 1); 
		// ���һ������ǩ�������ٴ�ʣ�µ�n-1������ҡ��k-1���š�
		case2 = LotteryNum(n - 1, k);     
		// ���һ����û����ǩ�������ٴ�ʣ�µ�n - 1������ҡ��k���š�
		num = case1 + case2;
	}
	return num;
}

int main()
{
	int n, k;
	cout << "����������ҡ�ŵĲ�������n����ǩ����k (k <= n)��\n";
	cin >> n >> k;
	if (k <= n)
		cout << "���п��ܵĽ���ĸ���Ϊ��" << LotteryNum(n, k) << endl;
	else
		cout << "��������";

    return 0;
}