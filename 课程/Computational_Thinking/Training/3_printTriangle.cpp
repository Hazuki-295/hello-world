#include <iostream>
using namespace std;

/* ��� �ױ߳�Ϊn ��ʵ�ĵ��������� */
void printTriangle(char c, int n)
{
	int blankNum = n - 1;
	for (int line = 1; line <= n; line++)
	{
		cout << string(blankNum, ' ');
		for (int i = 1; i <= line - 1; i++)
		{
			cout << c << " ";
		}
		cout << c;
		cout << string(blankNum, ' ') << endl;
		blankNum--;
	}
}

/* ��� �ױ߳�Ϊn ���οյ��������� */
void printTriangle2(char c, int n)
{
	int blankNum = n - 1;
	for (int line = 1; line <= n; line++) // ��ӡn��
	{
		cout << string(blankNum, ' ');
		for (int i = 1; i <= line - 1; i++)
		{
			if (line != n) // ����������һ�У��ο�������
			{
				if (i == 1)
					cout << c << " ";
				else
					cout << ' ' << " ";
			}
			else if (line == n) // ��������һ�У�ʵ��������
				cout << c << " ";
		}
		cout << c;
		cout << string(blankNum, ' ') << endl;
		blankNum--;
	}
}

int main()
{
	char c; int n;
	cin >> c >> n;
	printTriangle(c, n);
	return 0;
}