#include <iostream>
#include <unordered_map>
using namespace std;

struct grass_node
{
	// ��Ա
	int x, y; // ����
	// ���캯��
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
		// ����ɢ��һ���������������ͱ���Ҫ������������
		typedef size_t result_type;
		typedef grass_node argument_type; // Ĭ������£���������Ҫ==
		size_t operator() (const grass_node &s) const;
		// ���ǵ���ʹ�úϳɵĿ������Ƴ�Ա��Ĭ�Ϲ��캯��
	};
	size_t hash<grass_node>::operator() (const grass_node &s) const
	{
		return hash<int>() (s.x) ^ hash<int>() (s.y);
	}
} // �ر�std�����ռ�

/* Problem F. СN����ҵ�� */
int main()
{
	// �Ӳ����꣬����(Ȩֵ)
	int grass_num; cin >> grass_num;

	int x, y, w; // ���꣬Ȩֵ
	unordered_map<grass_node, int> grass;
	for (int i = 0; i < grass_num; i++) // �Ӳ���Ϣ
	{
		cin >> x >> y >> w;
		auto temp = grass_node(x, y);
		grass[temp] += w;
	}

	int search_num; cin >> search_num; // ��ѯ����
	int x1, y1, x2, y2; // ��ѯ�ľ���(������)
	for (int i = 0; i < search_num; i++)
	{
		int cost = 0; // �����Ӧ�����������Ӳݺķѵ������ܺ�
		cin >> x1 >> y1 >> x2 >> y2;

		for (auto temp : grass) // ��ÿһ���Ӳ�
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
