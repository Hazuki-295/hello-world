#include <iostream>
using namespace std;

/* �������ľ�̬����ʵ�� */
typedef struct {
	unsigned int number;
	unsigned int lchild, rchild;
} BiTNode, *BiTree;
/* ����������T[i].lchild == 0 && T[i].rchild == 0 */

/* ������������ */
int Depth(BiTree &T, int i)
{
	int depthval, depthLeft, depthRight;
	if (T[i].lchild == 0 && T[i].rchild == 0) // ����
		depthval = 1; // ������ڴ˴�
	else
	{
		depthLeft = Depth(T, T[i].lchild); // ����������
		depthRight = Depth(T, T[i].rchild); // ����������
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
	int n, r; // ������������� �� ���ڵ���
	cin >> n >> r;

	BiTree T = new BiTNode[n + 1]; // 0�ŵ�Ԫδ��
	T[0] = { 0,0,0 };

	for (int i = 1; i <= n; i++)
	{
		cin >> T[i].number >> T[i].lchild >> T[i].rchild;
	}

	/* ���ݱ������ */
	qsort(T, n + 1, sizeof(BiTNode), cmp);

	/* �Ӹ�������������� */
	int depth = Depth(T, r);

	cout << depth << endl;

	delete []T;

	return 0;
}