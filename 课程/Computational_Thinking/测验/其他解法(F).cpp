#include <iostream>
#include <unordered_map>
using namespace std;

struct grass_node
{
	// 成员
	int x, y; // 坐标
	// 构造函数
	grass_node(int _x, int _y) :x(_x), y(_y) {}
};

bool operator==(const grass_node &a, const grass_node &b)
{
	return (a.x == b.x && a.y == b.y);
}

namespace std
{
	template <>
	struct hash<grass_node>
	{
		// 用来散列一个无序容器的类型必须要定义下列类型
		typedef size_t result_type;
		typedef grass_node argument_type; // 默认情况下，此类型需要==
		size_t operator() (const grass_node &s) const;
		// 我们的类使用合成的拷贝控制成员和默认构造函数
	};
	size_t hash<grass_node>::operator() (const grass_node &s) const
	{
		return hash<int>() (s.x) ^ hash<int>() (s.y);
	}
} // 关闭std命名空间

/* Problem F. 小N的作业题 */
int main()
{
	// 杂草坐标，体力(权值)
	int grass_num; cin >> grass_num;

	int x, y, w; // 坐标，权值
	unordered_map<grass_node, int> grass;
	for (int i = 0; i < grass_num; i++) // 杂草信息
	{
		cin >> x >> y >> w;
		auto temp = grass_node(x, y);
		grass[temp] += w;
	}

	int search_num; cin >> search_num; // 查询次数
	int x1, y1, x2, y2; // 查询的矩形(闭区间)
	for (int i = 0; i < search_num; i++)
	{
		int cost = 0; // 清除相应矩形区域内杂草耗费的体力总和
		cin >> x1 >> y1 >> x2 >> y2;

		for (auto temp : grass) // 对每一颗杂草
		{
			if (x1 <= temp.first.x && temp.first.x <= x2) // x1<=x<=x2,y1<=y<=y2
			{
				if (y1 <= temp.first.y && temp.first.y <= y2)
				{
					cost += temp.second;
				}
			}
		}
		cout << cost << endl;
	}

	return 0;
}
