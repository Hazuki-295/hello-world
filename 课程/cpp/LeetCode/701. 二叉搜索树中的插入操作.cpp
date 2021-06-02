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

/* ����������������BST���ĸ��ڵ��Ҫ�������е�ֵ����ֵ��������������� */
class Solution {
public:
	TreeNode *insertIntoBST(TreeNode *root, int val) {
		if (root == nullptr) { // ԭ��Ϊ�գ��²���ļ�¼Ϊ�����
			TreeNode *node = new TreeNode(val);
			return node;       // ���ز��������������ĸ��ڵ�
		}

		TreeNode *cur = root;    // ��ǰ�����Ľ��
		TreeNode *parent = root; // ��Ҫ��¼��ǰ�����Ľ��ĸ��ڵ㣬�Ա���ɸ��ӽڵ�ĸ�ֵ
		while (cur != nullptr)   // �ҵ�����λ��
		{
			parent = cur; // ��¼��ǰ�����Ľ��ĸ��ڵ�
			if (val < cur->val) cur = cur->left; // ����������
			else cur = cur->right;               // ����������
		}
		TreeNode *node = new TreeNode(val);         // �²���Ľ��
		if (val < parent->val) parent->left = node; // ��ɸ��ӽڵ�ĸ�ֵ
		else parent->right = node;
		return root;
	}
};