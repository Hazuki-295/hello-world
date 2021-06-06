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
	/* 直接后继，中序遍历序列的下一个节点，即比当前节点大的最小节点。 */
	int successor(TreeNode *root) {
		root = root->right;           // 先取当前节点的右节点(后继在右子树)
		while (root->left != nullptr) // 然后一直取该节点的左节点，直到左节点为空
			root = root->left;
		return root->val; // 返回后继节点的值
	}

	/* 直接前驱，中序遍历序列的前一个节点，即比当前节点小的最大节点。 */
	int predecessor(TreeNode *root) {
		root = root->left;             // 先取当前节点的左节点(前驱在左子树)
		while (root->right != nullptr) // 然后一直取该结点的右节点，直到右节点为空
			root = root->right;
		return root->val; // 返回前驱节点的值
	}

	/* 删除二叉搜索树中的 key 对应的节点，返回二叉搜索树（有可能被更新）的根节点的引用。 */
	TreeNode *deleteNode(TreeNode *root, int key) {
		if (root == nullptr) return root; // 空树

		// 找到要删除的结点
		if (key < root->val) root->left = deleteNode(root->left, key);        // 小于，则转到左子树上删除
		else if (key > root->val) root->right = deleteNode(root->right, key); // 大于，则转到右子树上删除

		// 删除当前结点
		else {
			if (root->left == nullptr && root->right == nullptr) // 叶子结点，直接删除
				root = nullptr;
			else if (root->left == nullptr)  // 只有一颗右子树，用右子树替代
				root = root->right;
			else if (root->right == nullptr) // 只有一颗左子树，用左子树替代
				root = root->left;
			else { // 有左、右两棵子树
				root->val = successor(root); // 用直接后继替代(也可用直接前驱)
				root->right = deleteNode(root->right, root->val); // 递归地向下删去这个直接后继
			}
		}
		return root;
	}
};
