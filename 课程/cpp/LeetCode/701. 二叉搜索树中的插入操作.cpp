#include <iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 */
class Solution {
public:
	TreeNode *insertIntoBST(TreeNode *root, int val) {
		if (root == nullptr) { // 原树为空，新插入的记录为根结点
			TreeNode *node = new TreeNode(val);
			return node;       // 返回插入后二叉搜索树的根节点
		}

		TreeNode *cur = root;    // 当前遍历的结点
		TreeNode *parent = root; // 需要记录当前遍历的结点的父节点，以便完成父子节点的赋值
		while (cur != nullptr)   // 找到插入位置
		{
			parent = cur; // 记录当前遍历的结点的父节点
			if (val < cur->val) cur = cur->left; // 往左子树走
			else cur = cur->right;               // 往右子树走
		}
		TreeNode *node = new TreeNode(val);         // 新插入的结点
		if (val < parent->val) parent->left = node; // 完成父子节点的赋值
		else parent->right = node;
		return root;
	}
};