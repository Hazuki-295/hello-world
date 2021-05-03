#include <iostream>
using namespace std;

/* 二叉树的静态链表实现 */
typedef struct {
	unsigned int number;
	unsigned int lchild, rchild;
} BiTNode, *BiTree;
/* 叶子结点：T[i].lchild == 0 && T[i].rchild == 0 */

/* 求二叉树的深度 */
int Depth(BiTree &T, int i)
{
	int depthval, depthLeft, depthRight;
	if (T[i].lchild == 0 && T[i].rchild == 0) // 如果(子树)是叶子结点 或 进入了单侧空分支
		depthval = 1; // 深度为1
	else
	{
		depthLeft = Depth(T, T[i].lchild); // 求左子树深
		depthRight = Depth(T, T[i].rchild); // 求右子树深
		depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
	return depthval;
}

int cmp(const void *a, const void *b)
{
	if (((BiTNode *)a)->number > ((BiTNode *)b)->number)
		return 1;
	if (((BiTNode *)a)->number == ((BiTNode *)b)->number)
		return 0;
	else
		return -1;
}

int main()
{
	int n, r; // 二叉树结点数量 与 根节点编号
	cin >> n >> r;

	BiTree T = new BiTNode[n + 1]; // 0号单元未用
	T[0] = { 0,0,0 };

	for (int i = 1; i <= n; i++)
	{
		cin >> T[i].number >> T[i].lchild >> T[i].rchild;
	}

	/* 根据编号排序 */
	qsort(T, n + 1, sizeof(BiTNode), cmp);

	/* 从根结点出发，求深度 */
	int depth = Depth(T, r);

	cout << depth << endl;

	delete[]T;

	return 0;
}
