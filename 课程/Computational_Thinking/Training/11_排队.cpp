#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Queue // 排队
{
private:
	int group_num; // 小组数
	string number; // 执行操作的人
	size_t index;  // 以及他所在的组
	deque<string> Q;  // 队伍
	vector<vector<string>> groups; // 相熟的人定义为若干小组

public:
	// 构造函数
	Queue(int _group_num)
	{
		group_num = _group_num;
		groups = vector<vector<string>>(group_num);

		for (int i = 0; i < group_num; i++)
		{
			int size; cin >> size; // 小组人数
			string line; getline(cin, line);
			stringstream buffer(line);
			for (size_t j = 0; j < size; j++)
			{
				string temp; buffer >> temp;
				groups[i].push_back(temp);
			}
		}
	}

	// 操作
	void pattern_match(string &instrct)
	{
		stringstream buffer(instrct);
		string s1; buffer >> s1;
		if (s1 == "enqueue")
		{
			buffer >> number; // x开始排队
			search(number, index);
			enqueue();
		}
		if (s1 == "dequeue")
			dequeue();
		if (s1 == "deqteam")
		{
			buffer >> number; // x及相熟的人（若存在）离队
			search(number, index);
			deqteam();
		}
	}

	bool search(string x, size_t &_index) // 找到x所在的组
	{
		for (size_t i = 0; i < group_num; i++)
		{
			auto p = find(groups[i].begin(), groups[i].end(), x);
			if (p != groups[i].end())
			{
				_index = i;
				return true;
			}
		}
		return false; // 这个人没有组
	}

	void enqueue() // x开始排队
	{
		// 看看队列里面是否有熟人

		size_t size = Q.size(), _index; bool finished = false;
		for (int i = size - 1; i >= 0; i--) // 倒序遍历队伍里的每个人
		{
			if (search(Q[i], _index) == false) // 这个人没小组
				continue;
			if (_index == index) // 如果发现了熟人，他就会插队并排到熟人的后面
			{
				Q.insert(Q.begin() + _index + 1, number);
				finished = true;
				break;
			}
		}
		if (!finished) // 如果没有熟人在排队，他就只能在队尾排队
			Q.insert(Q.end(), number);
	}

	void dequeue() // 队头的人办理完业务离队
	{
		if (Q.size() != 0)
		{
			cout << Q.front() << " " << endl;
			Q.pop_front();
		}

	}

	void deqteam() // x及相熟的人（若存在）离队
	{
		size_t size = Q.size(), _index;
		deque<string>::iterator p1 = Q.end(), p2 = Q.end();
		for (size_t i = 0; i < size; i++) // 找到第一个同组的人
		{
			if (search(Q[i], _index)) // 这个人没小组
				continue;
			if (_index == index)
			{
				p1 = Q.begin() + i;
				break;
			}
		}
		for (int i = size - 1; i >= 0; i--) // 找到最后一个同组的人
		{
			if (search(Q[i], _index)) // 这个人没小组
				continue;
			if (_index == index)
			{
				p1 = Q.begin() + i + 1; // 的下一个位置
				break;
			}
		}
		vector<string> temp(p1, p2);
		for (auto x : temp)
			cout << x << " ";
		cout << endl;
		Q.erase(p1, p2); // x及相熟的人（若存在）离队
	}
};

int main()
{
	int blocks_num; int cases = 0;
	while (cin >> blocks_num && blocks_num != 0)
	{
		cout << "Case #" << ++cases << ":" << endl; char c = getchar();
		string line; Queue _Queue(blocks_num);
		while (getline(cin, line) && line != "stop")
		{
			_Queue.pattern_match(line);
		}
	}

	return 0;
}
