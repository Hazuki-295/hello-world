#include <iostream>
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


class Solution {
public:
	unordered_map<int, TreeNode *> fa; // key:���ֵ��val:���ڵ�
	unordered_map<int, bool> vis;      // ���ʱ��

	/* ������� */
	void dfs(TreeNode *root)
	{
		if (root->left != nullptr)       // ������ȱ���������
		{
			fa[root->left->val] = root;  // ��¼���Ӹ��ڵ���Ϣ
			dfs(root->left);
		}
		if (root->right != nullptr)      // ������ȱ���������
		{
			fa[root->right->val] = root; // ��¼�Һ��Ӹ��ڵ���Ϣ
			dfs(root->right);
		}
	}

	/* ����������� */
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
	{
		fa[root->val] = nullptr; // ���޸��ڵ�

		dfs(root); // �õ����ӹ�ϵ��Ϣ

		while (p != nullptr)    // ���Ϸ���p������
		{
			vis[p->val] = true; // ���ʱ��
			p = fa[p->val];     // ���ʸ��ڵ�ĸ��ڵ�
		}
		while (q != nullptr)    // ���Ϸ���q������
		{
			if (vis[q->val])    // �������pʱ�ѷ��ʹ�
				return q;       // ��Ϊ��������
			q = fa[q->val];
		}
		return nullptr; // ����pʱδ���ʵ�q�����ȣ��޹�������
	}
};
