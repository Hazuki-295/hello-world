#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include <algorithm>
using namespace std;

int main()
{
	int name_num, L; // 文件名数、列宽

	while (cin >> name_num >> L)
	{
		set<int> wide; // 求单词最大宽度

		vector<string> name; string temp;
		for (int i = 0; i < name_num; i++)
		{
			cin >> temp;
			name.push_back(temp);
			wide.insert(temp.size());
		}
		sort(name.begin(), name.end());

		cout << string(L, '-') << endl;

		int w = *(wide.rbegin());  // 单词最大宽度

		int N = (L + 2) / (2 + w); // 每行元素个数
		// 每行元素个数 = (L+2)/(2+w)
		// 则所需行数 = 所有元素个数/每行元素个数，向上取整

		int line_num = name.size() / N;
		bool incomplete = false; // 是否存在不完整的行？
		int exceede = name.size() % N;
		if (exceede != 0)
		{
			line_num++;
			incomplete = true;
		}

		/* 自上而下、从左到右按字典序排列 */
		vector<vector<string>> namelines(line_num); // 要多少行?? 

		// 文件列表按字典序左对齐的方式显示为若干列
		// 列宽由文件名的最大长度确定

		int index = 0;
		for (int i = 0; i < name.size(); i++)
		{
			if (incomplete) // 存在不完整的行
			{
				if (index == line_num - 1 && namelines[index].size() == exceede) // 最后一行满了
				{
					i--; index = (index + 1) % line_num; // 此行不填充
					continue;
				}
			}

			namelines[index].push_back(name[i]);
			index = (index + 1) % line_num;
		}

		for (int i = 0; i < line_num; i++)
		{
			/* 格式控制 */
			ios init(nullptr);
			init.copyfmt(cout); // 使用copyfmt保存cout的初始格式

			int j;
			for (j = 0; j < namelines[i].size() - 1; j++)
				cout << setw(w) << left << namelines[i][j] << "  "; // 列间用2个空格分割

			/* 格式恢复 */
			cout.copyfmt(init);

			cout << left << namelines[i][j] << endl; // 最后一列后无空格
		}
	}

	return 0;
}
