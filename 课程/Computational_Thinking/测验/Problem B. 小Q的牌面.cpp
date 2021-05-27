#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

/* Problem B. СQ������ */
int main()
{
	// ��ÿ������������������ͬ������Ԫ��
	vector<set<int>> cards(4);
	
	string line; set<int> allkind;

	for (int i = 0; i < 4; i++) // ��ȡ4��
	{
		getline(cin, line);
		stringstream buffer(line); // �󶨸ն������

		int n; buffer >> n; // �û�ɫԪ�ظ���
		int temp;
		for (int j = 0; j < n; j++)
		{
			buffer >> temp;
			cards[i].insert(temp);
			allkind.insert(temp);    // ���п��ܵ���ֵ
		}
	}
	int size = allkind.size();

	int count = 0;
	for (int i = 0; i < 4; i++) // ��������
	{
		for (auto x : allkind)
		{
			if (find(cards[i].begin(), cards[i].end(), x) == cards[i].end())
			{
				cards[i].insert(x); // �޴�Ԫ�أ����
				count++; // �����Ԫ�ظ���
			}
		}
	}

	cout << count << endl;
	
}