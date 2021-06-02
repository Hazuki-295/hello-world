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