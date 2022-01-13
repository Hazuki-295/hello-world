﻿#include <iostream>
#include <stack>
#include <queue>
using namespace std;

#define MaxSize 50

/* 二叉树的二叉链表存储表示 */
template<typename T> struct BiTNode
{
	// 成员
	T data; BiTNode *lchild, *rchild; // 值、左右孩子指针
	// 构造函数
	BiTNode(T x) :data(x), lchild(nullptr), rchild(nullptr) {}
};
template<typename T> using BiTree = BiTNode<T> *;

/* 二叉树模板类 */
template<typename T> class BinTree
{
private:
	using ElemType = T;
	using BiTNode = BiTNode<T>;
	using BiTree = BiTree<T>;

	BiTree T = nullptr; // 指向树根的指针

	void (*visit)(ElemType &e) = PrintElement;

public:
	// 对象调用(递归算法)
	void CreateBiTree() { CreateBiTree(T); }
	void CountLeaf(int &count) { CountLeaf(T, count); }
	void CountNode(int &count) { CountNode(T, count); }
	void Depth() { Depth(T); }
	void InOrder() { InOrder(T); }
	void PreOrder() { PreOrder(T); }
	void PostOrder() { PostOrder(T); }


	/* 按先序扩展序列(字符)，建立二叉树的二叉链表 */
	void CreateBiTree(BiTree &T)
	{
		char c;
		if (cin >> c)
		{
			if (c == '#')     // '#'表示空树
				T = nullptr;
			else
			{
				T = new BiTNode(c);      // 生成根结点  
				CreateBiTree(T->lchild); // 递归构造左子树
				CreateBiTree(T->rchild); // 递归构造右子树
			}
		}
	}

	/* 访问结点 */
	static void PrintElement(ElemType &e) { cout << e; }

	/* 统计二叉树中叶子结点的个数 */
	void CountLeaf(BiTree T, int &count)
	{
		if (T != nullptr)
		{
			if ((!T->lchild) && (!T->rchild)) // 如果是叶子结点
				count++; // 对叶子结点计数
			CountLeaf(T->lchild, count);
			CountLeaf(T->rchild, count);
		}
	}

	/* 统计二叉树中结点的个数 */
	void CountNode(BiTree T, int &count)
	{
		if (T != nullptr)
		{
			//if ((!T->lchild) && (!T->rchild)) // 如果是叶子结点
			count++; // 对叶子结点计数
			CountNode(T->lchild, count);
			CountNode(T->rchild, count);
		}
	}

	/* 求二叉树的深度 */
	int Depth(BiTree T)
	{
		int depthval, depthLeft, depthRight;
		if (T == nullptr)
			depthval = 0;
		else
		{
			depthLeft = Depth(T->lchild);   // 递归求左子树深
			depthRight = Depth(T->rchild);  // 递归求右子树深
			depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight); // 树根深度，为左右子树的最大深度+1
		}
		return depthval;
	}

	/* 先序遍历二叉树 */
	void PreOrder(BiTree T)
	{
		if (T) {
			visit(T->data);             // 访问根结点
			PreOrder(T->lchild, visit); // 遍历左子树
			PreOrder(T->rchild, visit); // 遍历右子树
		}
	}

	/* 中序遍历二叉树 */
	void InOrder(BiTree T)
	{
		if (T) {
			InOrder(T->lchild, visit); // 遍历左子树
			visit(T->data);            // 访问根结点
			InOrder(T->rchild, visit); // 遍历右子树
		}
	}

	/* 后序遍历二叉树 */
	void PostOrder(BiTree T)
	{
		if (T) {
			PostOrder(T->lchild, visit); // 遍历左子树
			PostOrder(T->rchild, visit); // 遍历右子树
			visit(T->data);              // 访问根结点
		}
	}


	/* 中序遍历二叉树(非递归算法) */
	void InOrder2()
	{
		stack<BiTree> S; BiTree p = T; // 初始化栈S; p是遍历指针
		while (p || !S.empty()) // 栈不空(存在待访问结点) 或 p不空(中序遍历的树不是空树) 时循环
		{
			if (p) // 一路向左 (或 右子树不空，中序遍历之)
			{
				S.push(p);     // 当前结点入栈
				p = p->lchild; // 左孩子不空，一直向左走
			}
			else // 出栈，并转向出栈结点的右子树
			{
				p = S.top(); S.pop(); // 栈顶元素出栈
				visit(p->data);       // 访问出栈结点
				p = p->rchild;        // 向右子树走，p赋值为当前结点的右孩子
									  // 若右孩子为空，该出栈结点遍历完毕，则继续出栈
			} // 返回while循环，继续进入if-else语句
		}
	}

	/* 先序遍历二叉树(非递归算法) */
	void PreOrder2()
	{
		stack<BiTree> S; BiTree p = T; // 初始化栈S; p是遍历指针
		while (p || !S.empty()) // 栈不空(存在待访问结点) 或 p不空(先序遍历的树不是空树) 时循环
		{
			if (p) // 一路向左 (或 右子树不空，先序遍历之)
			{
				visit(p->data); S.push(p); // 访问当前结点，并入栈
				p = p->lchild;             // 左孩子不空，一直向左走
			}
			else // 出栈，并转向出栈结点的右子树
			{
				p = S.top(); S.pop(); // 栈顶元素出栈
				p = p->rchild;        // 向右子树走，p赋值为当前结点的右孩子
									  // 若右孩子为空，该出栈结点遍历完毕，则继续出栈
			} // 返回while循环，继续进入if-else语句
		}
	}

	/* 层次遍历二叉树 */
	void LevelOrder()
	{
		queue<BiTree> Q; BiTree p = T; // 初始化辅助队列; p是遍历指针

		Q.push(T); // 将根结点入队
		while (!Q.empty()) // 队列不空则循环
		{
			p = Q.front(); Q.pop(); // 队头结点出队
			visit(p->data); // 访问出队结点

			if (p->lchild != NULL)
				Q.push(p->lchild); // 左子树不空，则左子树根结点入队
			if (p->rchild != NULL)
				Q.push(p->rchild); // 右子树不空，则右子树根结点入队
		}
	}
};

int main()
{
	BinTree<char> T;
	T.CreateBiTree();

	T.InOrder2(); cout << endl;
	T.LevelOrder(); cout << endl;

	return 0;
}