#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void Solution(int x1, int x2) // ������
{
	int a = 1;
	int b = -(x1 + x2);
	int c = x1 * x2;
	printf("%d %d %d\n", a, b, c);
}

/* Problem D. ��ѧ���� */
int main()
{
	// ��֪һԪ���η��̵����������������һԪ���η��̡�
	// ���ж���⣬�������һ�ּ��ɣ���Ҫ��������ϵ������ֵ������100000��

	int T, a, b; cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> a >> b;
		Solution(a, b);
	}

	return 0;
}