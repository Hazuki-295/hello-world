#include <iostream>
using namespace std;

int LotteryNum(int n, int k)
{
	int num, case1, case2;
	if (n == k || k == 0) // 解
		num = 1;
	else // C(n,k) = C(n-1,k-1) + C(n-1,k)
	{
		case1 = LotteryNum(n - 1, k - 1); 
		// 如果一个号中签，接着再从剩下的n-1个号中摇出k-1个号。
		case2 = LotteryNum(n - 1, k);     
		// 如果一个号没有中签，接着再从剩下的n - 1个号中摇出k个号。
		num = case1 + case2;
	}
	return num;
}

int main()
{
	int n, k;
	cout << "请输入汽车摇号的参与人数n、中签人数k (k <= n)。\n";
	cin >> n >> k;
	if (k <= n)
		cout << "所有可能的结果的个数为：" << LotteryNum(n, k) << endl;
	else
		cout << "输入有误。";

    return 0;
}