#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
	// 成员
	int val; TreeNode *left, *right; // 值、左右孩子
	// 构造函数
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int main()
{
	// 记录父子关系信息
	unordered_map<int, TreeNode *> fa; // key:结点值、val:父结点
	unordered_map<int, bool> vis;      // 访问标记

	int node_num, search_num; // 结点数、查询次数
	cin >> node_num >> search_num;

	vector<TreeNode *>treenodes;

	TreeNode *p;
	for (int i = 0; i < node_num + 1; i++) // 树节点信息从1计起(0号未用)
	{
		p = new TreeNode(i); // 创建结点
		treenodes.push_back(p);
	}

	int father, child;
	for (int i = 0; i < node_num - 1; i++) // 父子关系(n-1条边)
	{
		cin >> father >> child;
		TreeNode *f, *c;
		f = treenodes[father];
		c = treenodes[child];

		fa[c->val] = f; // 存入父结点信息
	}

	for (int i = 1; i <= node_num; i++)
	{
		auto p = fa.find(i);
		if (p == fa.end()) // 找到根结点
			fa[i] = nullptr;
	}

	int a, b; int cases = 0; // 存放查询的两人
	for (int i = 0; i < search_num; i++) // 搜索最近公共祖先
	{
		cin >> a >> b;
		cout << "Case " << ++cases << ": ";

		if (a > node_num || b > node_num)
		{
			cout << "Invalid\n";
			continue;
		}
		TreeNode *p, *q; // 查询的两个结点
		p = treenodes[a];
		q = treenodes[b];
		TreeNode *r = nullptr; // 存放查询结果

		while (p != nullptr)    // 往上访问p的祖先
		{
			vis[p->val] = true; // 访问标记
			p = fa[p->val];     // 访问父节点的父节点
		}
		while (q != nullptr)    // 往上访问q的祖先
		{
			if (vis[q->val])    // 如果访问p时已访问过
			{
				r = q; // 其为公共祖先
				break;
			}
			q = fa[q->val];
		}

		if (r != nullptr) // 访问p时未访问到q的祖先，无公共祖先
			cout << r->val << endl;
		vis.clear(); // 清空访问标记
	}

	return 0;
}
