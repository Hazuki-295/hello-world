#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

/* Problem B. 小Q的牌面 */
int main()
{
	// 将每个向量扩充至含有相同个数的元素
	vector<set<int>> cards(4);

	string line; set<int> allkind;

	for (int i = 0; i < 4; i++) // 读取4行
	{
		getline(cin, line);
		stringstream buffer(line); // 绑定刚读入的行

		int n; buffer >> n; // 该花色元素个数
		int temp;
		for (int j = 0; j < n; j++)
		{
			buffer >> temp;
			cards[i].insert(temp);
			allkind.insert(temp);    // 所有可能的数值
		}
	}
	int size = allkind.size();

	int count = 0;
	for (int i = 0; i < 4; i++) // 扩充向量
	{
		for (auto x : allkind)
		{
			if (find(cards[i].begin(), cards[i].end(), x) == cards[i].end())
			{
				cards[i].insert(x); // 无此元素，填充
				count++; // 补充的元素个数
			}
		}
	}

	cout << count << endl;

	return 0;
}
