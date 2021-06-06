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
	/* ֱ�Ӻ�̣�����������е���һ���ڵ㣬���ȵ�ǰ�ڵ�����С�ڵ㡣 */
	int successor(TreeNode *root) {
		root = root->right;           // ��ȡ��ǰ�ڵ���ҽڵ�(�����������)
		while (root->left != nullptr) // Ȼ��һֱȡ�ýڵ����ڵ㣬ֱ����ڵ�Ϊ��
			root = root->left;
		return root->val; // ���غ�̽ڵ��ֵ
	}

	/* ֱ��ǰ��������������е�ǰһ���ڵ㣬���ȵ�ǰ�ڵ�С�����ڵ㡣 */
	int predecessor(TreeNode *root) {
		root = root->left;             // ��ȡ��ǰ�ڵ����ڵ�(ǰ����������)
		while (root->right != nullptr) // Ȼ��һֱȡ�ý����ҽڵ㣬ֱ���ҽڵ�Ϊ��
			root = root->right;
		return root->val; // ����ǰ���ڵ��ֵ
	}

	/* ɾ�������������е� key ��Ӧ�Ľڵ㣬���ض������������п��ܱ����£��ĸ��ڵ�����á� */
	TreeNode *deleteNode(TreeNode *root, int key) {
		if (root == nullptr) return root; // ����

		// �ҵ�Ҫɾ���Ľ��
		if (key < root->val) root->left = deleteNode(root->left, key);        // С�ڣ���ת����������ɾ��
		else if (key > root->val) root->right = deleteNode(root->right, key); // ���ڣ���ת����������ɾ��

		// ɾ����ǰ���
		else {
			if (root->left == nullptr && root->right == nullptr) // Ҷ�ӽ�㣬ֱ��ɾ��
				root = nullptr;
			else if (root->left == nullptr)  // ֻ��һ���������������������
				root = root->right;
			else if (root->right == nullptr) // ֻ��һ���������������������
				root = root->left;
			else { // ��������������
				root->val = successor(root); // ��ֱ�Ӻ�����(Ҳ����ֱ��ǰ��)
				root->right = deleteNode(root->right, root->val); // �ݹ������ɾȥ���ֱ�Ӻ��
			}
		}
		return root;
	}
};
