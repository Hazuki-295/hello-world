#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Instrcts
{
private:
	int block_num; // 积木数
	int a, b;      // 每次操作的对象
	size_t index_a, index_b;       // a、b所在列
	vector<int>::iterator p1, p2;  // a、b所在列中位置
	vector<vector<int>> blocks; // 积木列
	stack<int> S; // 辅助栈
public:
	// 构造函数
	Instrcts(int _block_num)
	{
		block_num = _block_num;
		blocks = vector<vector<int>>(block_num);
		for (int i = 0; i < block_num; i++)
		{
			blocks[i].push_back(i); // 每个积木块所在的位置为其对应的编号
		}
	}

	// 操作
	void pattern_match(string &instrct)
	{
		stringstream buffer(instrct);
		string s1, s2;
		buffer >> s1 >> a >> s2 >> b;
		if (a == b) return; // 不执行操作
		for (size_t i = 0; i < block_num; i++) // 查找a，b位置
		{
			p1 = find(blocks[i].begin(), blocks[i].end(), a);
			p2 = find(blocks[i].begin(), blocks[i].end(), b);
			if (p1 != blocks[i].end() && p2 != blocks[i].end()) // 在同一列中
				return; // 不执行操作
			if (p1 != blocks[i].end())
				index_a = i;
			if (p2 != blocks[i].end())
				index_b = i;
		}

		if (s1 == "mv" && s2 == "on")
			move_on();
		if (s1 == "mv" && s2 == "ov")
			move_above();
		if (s1 == "st" && s2 == "on")
			shift_on();
		if (s1 == "st" && s2 == "ov")
			shift_above();
		if (s1 == "xh" && s2 == "an")
			exchange();
	}

	void reset(int block) // 恢复一列
	{
		size_t index = 0;
		if (block == a)
			index = index_a;
		if (block == b)
			index = index_b;

		auto p = blocks[index].back();
		while (p != block)
		{
			size_t poi = p; // 每个积木块所在的位置为其对应的编号
			blocks[poi].push_back(p);  // 放回原位
			blocks[index].pop_back();  // 移除，p

			p = blocks[index].back();
		}
	}

	void move_on()
	{
		reset(a); // 将a和b所在列a、b之上的所有积木块
		reset(b); // 恢复到最初其所在的位置上
		blocks[index_b].push_back(a); // 然后将积木块a搁置在积木块b之上
		blocks[index_a].pop_back();
	}

	void move_above()
	{
		// 将积木块a之上的所有积木块恢复到最初其所在的位置上
		reset(a);
		// 然后将积木块a放置在积木块b所在列的顶端
		blocks[index_b].push_back(a);
		blocks[index_a].pop_back();
	}

	// 将积木块b之上的所有积木块，存入栈
	void shift(int block)
	{
		size_t index = 0;
		if (block == a)
			index = index_a;
		if (block == b)
			index = index_b;

		auto p = blocks[index].back();
		while (p != block)
		{
			S.push(p); // 放入栈
			blocks[index].pop_back();  // 移除，p

			p = blocks[index].back();
		}
		S.push(p); // 放入栈
		blocks[index].pop_back();  // 移除
	}

	void shift_on()
	{
		// 将积木块b之上的所有积木块恢复到最初其所在的位置上，
		reset(b);
		// 然后将积木块a及其上的所有积木放置在积木块b之上。
		shift(a); int temp;
		while (!S.empty())
		{
			temp = S.top(); S.pop();
			blocks[index_b].push_back(temp);
		}
	}

	void shift_above()
	{
		// 将积木块a及其上的所有积木
		shift(a); int temp;
		// 放置在积木块b所在列的顶端。
		while (!S.empty())
		{
			temp = S.top(); S.pop();
			blocks[index_b].push_back(temp);
		}
	}

	void exchange()
	{
		swap(blocks[index_a], blocks[index_b]);
	}

	void Print() // 打印每一列
	{
		for (int i = 0; i < block_num; i++)
		{
			cout << i << ":";
			for (auto x : blocks[i])
				cout << " " << x;
			cout << endl;
		}
	}
};

int main()
{
	int blocks_num; cin >> blocks_num;
	string line; Instrcts Block(blocks_num);
	char c = getchar();
	while (getline(cin, line) && line != "q")
	{
		Block.pattern_match(line);
	}
	Block.Print();

	return 0;
}
