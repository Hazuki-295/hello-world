#include <iostream>
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


class Solution {
public:
	unordered_map<int, TreeNode *> fa; // key:结点值、val:父节点
	unordered_map<int, bool> vis;      // 访问标记

	/* 深度优先 */
	void dfs(TreeNode *root)
	{
		if (root->left != nullptr)       // 深度优先遍历左子树
		{
			fa[root->left->val] = root;  // 记录左孩子父节点信息
			dfs(root->left);
		}
		if (root->right != nullptr)      // 深度优先遍历右子树
		{
			fa[root->right->val] = root; // 记录右孩子父节点信息
			dfs(root->right);
		}
	}

	/* 最近公共祖先 */
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
	{
		fa[root->val] = nullptr; // 根无父节点

		dfs(root); // 得到父子关系信息

		while (p != nullptr)    // 往上访问p的祖先
		{
			vis[p->val] = true; // 访问标记
			p = fa[p->val];     // 访问父节点的父节点
		}
		while (q != nullptr)    // 往上访问q的祖先
		{
			if (vis[q->val])    // 如果访问p时已访问过
				return q;       // 其为公共祖先
			q = fa[q->val];
		}
		return nullptr; // 访问p时未访问到q的祖先，无公共祖先
	}
};
