#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
	// ��Ա
	int val; TreeNode *left, *right; // ֵ�����Һ���
	// ���캯��
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int main()
{
	// ��¼���ӹ�ϵ��Ϣ
	unordered_map<int, TreeNode *> fa; // key:���ֵ��val:�����
	unordered_map<int, bool> vis;      // ���ʱ��

	int node_num, search_num; // ���������ѯ����
	cin >> node_num >> search_num;

	vector<TreeNode *>treenodes;

	TreeNode *p;
	for (int i = 0; i < node_num + 1; i++) // ���ڵ���Ϣ��1����(0��δ��)
	{
		p = new TreeNode(i); // �������
		treenodes.push_back(p);
	}

	int father, child;
	for (int i = 0; i < node_num - 1; i++) // ���ӹ�ϵ(n-1����)
	{
		cin >> father >> child;
		TreeNode *f, *c;
		f = treenodes[father];
		c = treenodes[child];

		fa[c->val] = f; // ���븸�����Ϣ
	}

	for (int i = 1; i <= node_num; i++)
	{
		auto p = fa.find(i);
		if (p == fa.end()) // �ҵ������
			fa[i] = nullptr;
	}

	int a, b; int cases = 0; // ��Ų�ѯ������
	for (int i = 0; i < search_num; i++) // ���������������
	{
		cin >> a >> b;
		cout << "Case " << ++cases << ": ";

		if (a > node_num || b > node_num)
		{
			cout << "Invalid\n";
			continue;
		}
		TreeNode *p, *q; // ��ѯ���������
		p = treenodes[a];
		q = treenodes[b];
		TreeNode *r = nullptr; // ��Ų�ѯ���

		while (p != nullptr)    // ���Ϸ���p������
		{
			vis[p->val] = true; // ���ʱ��
			p = fa[p->val];     // ���ʸ��ڵ�ĸ��ڵ�
		}
		while (q != nullptr)    // ���Ϸ���q������
		{
			if (vis[q->val])    // �������pʱ�ѷ��ʹ�
			{
				r = q; // ��Ϊ��������
				break;
			}
			q = fa[q->val];
		}

		if (r != nullptr) // ����pʱδ���ʵ�q�����ȣ��޹�������
			cout << r->val << endl;
		vis.clear(); // ��շ��ʱ��
	}

	return 0;
}
