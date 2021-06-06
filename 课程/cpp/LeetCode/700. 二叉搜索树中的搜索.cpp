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

/* ����������������BST���ĸ��ڵ��һ��ֵ�� ����Ҫ��BST���ҵ��ڵ�ֵ���ڸ���ֵ�Ľڵ㡣 */
class Solution {
public:
	TreeNode *searchBST(TreeNode *root, int val) {
		while (root != nullptr && val != root->val) { // �����ջ���ڸ����ֵ�������ѭ��
			if (val < root->val)      // С�ڣ������������ϲ���
				root = root->left;
			else if (val > root->val) // ���ڣ������������ϲ���
				root = root->right;
		}
		return root; // �����Ըýڵ�Ϊ��������������㲻���ڣ��򷵻� NULL
	}
};

/* �ݹ�ʵ�� */
class Solution {
public:
	TreeNode *searchBST(TreeNode *root, int val) {
		if (root == nullptr || val == root->val) // �����ջ���ڸ����ֵ�������ѭ��
			return root;
		return val < root->val ? searchBST(root->left, val) : searchBST(root->right, val); // С�ڣ������������ϲ���
	}
};