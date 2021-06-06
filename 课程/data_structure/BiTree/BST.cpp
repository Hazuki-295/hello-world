#include <iostream>
using namespace std;

/* 二叉树的二叉链表存储表示 */
template<typename T> struct BiTNode
{
	// 成员
	T data; BiTNode *lchild, *rchild; // 值、左右孩子指针
	// 构造函数
	BiTNode() : data(), lchild(nullptr), rchild(nullptr) {}
	BiTNode(T x) :data(x), lchild(nullptr), rchild(nullptr) {}
	BiTNode(T x, BiTNode *lchild, BiTNode *rchild) : data(x), lchild(lchild), rchild(rchild) {}
};
template<typename T> using BiTree = BiTNode<T> *;

template<typename T> class BST
{
private:
	using ElemType = T;
	using BiTNode = BiTNode<T>;
	using BiTree = BiTree<T>;

	BiTree root = nullptr; // 指向树根的指针

	void (*visit)(ElemType &e) = printElement;

public:
	/* 二叉排序树的查找 */
	BiTNode *searchBST(BiTree T, ElemType key) {
		while (T != nullptr && key != T->data) {   // 若树空或等于根结点值，则结束循环
			if (key < T->data)      // 小于，则在左子树上查找
				T = T->lchild;
			else if (key > T->data) // 大于，则在右子树上查找
				T = T->rchild;
		}
		return T; // 返回以该节点为根的子树。若结点不存在，则返回 NULL
	}

	/* 二叉排序树的插入 */
	bool insertBST(BiTree &T, ElemType val)
	{
		if (T == nullptr) { // 原树为空，新插入的记录为根结点
			T = new BiTNode;
			T->data = val;
			T->lchild = T->rchild = nullptr;
			return true;
		}
		else if (val == T->data) // 树中存在相同关键字的结点，插入失败
			return false;
		else if (val < T->data) // 插入到T的左子树
			return insertBST(T->lchild, val);
		else                    // 插入到T的右子树
			return insertBST(T->rchild, val);
	}

	/* 二叉排序树的构造 */
	void creatBST(int n)
	{
		root = nullptr; ElemType temp; // 初始时为空树
		for (int i = 0; i < n; i++)    // 树中含有n个结点
		{
			cin >> temp;
			insertBST(root, temp);
		}
	}

	/* 访问结点 */
	static void printElement(ElemType &e) { cout << e << " "; }

	/* 接口 */
	BiTNode *searchBST(ElemType key) { return searchBST(root, key); }
	bool insertBST(ElemType val) { return insertBST(root, val); }
	void inorderTraverse() { inorderTraverse(root); }

	/* 中序遍历 */
	void inorderTraverse(BiTree T)
	{
		if (T != nullptr)
		{
			inorderTraverse(T->lchild); // 遍历左子树
			visit(T->data);             // 访问根结点
			inorderTraverse(T->rchild); // 遍历右子树
		}
	}
};

int main()
{
	int nodeNum; cin >> nodeNum;
	BST<int> Tree; Tree.creatBST(nodeNum);
	Tree.inorderTraverse(); cout << endl;// 中序遍历原二叉排序树后的有序序列
	int val; cin >> val;
	if (Tree.searchBST(val) == nullptr)
	{
		Tree.insertBST(val);
		cout << "插入成功" << endl;
		Tree.inorderTraverse(); cout << endl;
	}
	else
	{
		cout << "查找成功 " << endl;
	}
	return 0;
}