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

/* 给定二叉搜索树（BST）的根节点和一个值。 你需要在BST中找到节点值等于给定值的节点。 */
class Solution {
public:
	TreeNode *searchBST(TreeNode *root, int val) {
		while (root != nullptr && val != root->val) { // 若树空或等于根结点值，则结束循环
			if (val < root->val)      // 小于，则在左子树上查找
				root = root->left;
			else if (val > root->val) // 大于，则在右子树上查找
				root = root->right;
		}
		return root; // 返回以该节点为根的子树。若结点不存在，则返回 NULL
	}
};

/* 递归实现 */
class Solution {
public:
	TreeNode *searchBST(TreeNode *root, int val) {
		if (root == nullptr || val == root->val) // 若树空或等于根结点值，则结束循环
			return root;
		return val < root->val ? searchBST(root->left, val) : searchBST(root->right, val); // 小于，则在左子树上查找
	}
};