#include <iostream>
#include <queue>
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

template<typename ElemType> class BST
{
private:
	using BiTNode = ::BiTNode<ElemType>;
	using BiTree = ::BiTree<ElemType>;

	BiTree root = nullptr; // 指向树根的指针

public:
	queue<int> print; // 用于处理输出结果

	/* 二叉排序树的查找 */
	BiTNode *searchBST(BiTree T, ElemType key, int &count) {
		count = 1;
		while (T != nullptr && key != T->data) {   // 若树空或等于根结点值，则结束循环
			count++;
			if (key < T->data) T = T->lchild;      // 小于，则在左子树上查找
			else if (key > T->data) T = T->rchild; // 大于，则在右子树上查找
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
	void visit(ElemType &e) { print.push(e); }

	/* 接口 */
	BiTNode *searchBST(ElemType key, int &count) { return searchBST(root, key, count); }
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

/* 编译器版本不同，平台上课通过版本 */
int main()
{
	int nodeNum; cin >> nodeNum;
	BST<int> Tree; Tree.creatBST(nodeNum);
	Tree.inorderTraverse(); // 中序遍历原二叉排序树后的有序序列
	auto size = Tree.print.size();
	for (int i = 0; i < size - 1; i++)
	{
		cout << Tree.print.front() << ' ';
		Tree.print.pop();
	}
	cout << Tree.print.front() << endl; Tree.print.pop();

	int count, val; cin >> val;
	if (Tree.searchBST(val, count) == nullptr)
	{
		Tree.insertBST(val);
		cout << "插入成功" << endl;
		Tree.inorderTraverse();
		auto size = Tree.print.size();
		for (int i = 0; i < size - 1; i++)
		{
			cout << Tree.print.front() << ' ';
			Tree.print.pop();
		}
		cout << Tree.print.front() << endl; Tree.print.pop();
	}
	else
	{
		cout << "查找成功 " << count << endl;
	}
	return 0;
}
