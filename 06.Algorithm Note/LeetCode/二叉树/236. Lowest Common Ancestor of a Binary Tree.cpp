#include <iostream>
#include <unordered_map>

using namespace std;

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    unordered_map<int, TreeNode *> fa; // <value, pointer to parent>
    unordered_map<int, bool> vis;      // visited?

    /* dfs to record the information of every node's parent, each node has a unique value. */
    void dfs(TreeNode *root) {
        if (root->left != nullptr) { // current node has left child?
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != nullptr) {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        fa[root->val] = nullptr; // tree root has no parent

        dfs(root); // run dfs to get child-parent information of the tree

        while (p != nullptr) {  // start from one of the node p, go up to visit p's ancestors
            vis[p->val] = true;
            p = fa[p->val];
        }
        while (q != nullptr) {  // start from q, go up to visit q's ancestors
            if (vis[q->val]) {  // once visited before, the lowest common ancestor
                return q;
            }
            q = fa[q->val];
        }
        return nullptr;
    }
};