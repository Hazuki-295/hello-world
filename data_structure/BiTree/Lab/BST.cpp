#include <iostream>
using namespace std;

/* �������Ķ��������洢��ʾ */
template<typename T> struct BiTNode
{
	// ��Ա
	T data; BiTNode *lchild, *rchild; // ֵ�����Һ���ָ��
	// ���캯��
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

	BiTree root = nullptr; // ָ��������ָ��

	void (*visit)(ElemType &e) = printElement;

public:
	/* �����������Ĳ��� */
	BiTNode *searchBST(BiTree T, ElemType key, int &count) {
		count = 1;
		while (T != nullptr && key != T->data) {   // �����ջ���ڸ����ֵ�������ѭ��
			count++;
			if (key < T->data) T = T->lchild;      // С�ڣ������������ϲ���
			else if (key > T->data) T = T->rchild; // ���ڣ������������ϲ���
		}
		return T; // �����Ըýڵ�Ϊ��������������㲻���ڣ��򷵻� NULL
	}

	/* �����������Ĳ��� */
	bool insertBST(BiTree &T, ElemType val)
	{
		if (T == nullptr) { // ԭ��Ϊ�գ��²���ļ�¼Ϊ�����
			T = new BiTNode;
			T->data = val;
			T->lchild = T->rchild = nullptr;
			return true;
		}
		else if (val == T->data) // ���д�����ͬ�ؼ��ֵĽ�㣬����ʧ��
			return false;
		else if (val < T->data) // ���뵽T��������
			return insertBST(T->lchild, val);
		else                    // ���뵽T��������
			return insertBST(T->rchild, val);
	}

	/* �����������Ĺ��� */
	void creatBST(int n)
	{
		root = nullptr; ElemType temp; // ��ʼʱΪ����
		for (int i = 0; i < n; i++)    // ���к���n�����
		{
			cin >> temp;
			insertBST(root, temp);
		}
	}

	/* ���ʽ�� */
	static void printElement(ElemType &e) { cout << e << " "; }

	/* �ӿ� */
	BiTNode *searchBST(ElemType key, int &count) { return searchBST(root, key, count); }
	bool insertBST(ElemType val) { return insertBST(root, val); }
	void inorderTraverse() { inorderTraverse(root); }

	/* ������� */
	void inorderTraverse(BiTree T)
	{
		if (T != nullptr)
		{
			inorderTraverse(T->lchild); // ����������
			visit(T->data);             // ���ʸ����
			inorderTraverse(T->rchild); // ����������
		}
	}
};

int main()
{
	int nodeNum; cin >> nodeNum;
	BST<int> Tree; Tree.creatBST(nodeNum);
	Tree.inorderTraverse(); cout << endl;// �������ԭ���������������������
	int count, val; cin >> val;
	if (Tree.searchBST(val, count) == nullptr)
	{
		Tree.insertBST(val);
		cout << "����ɹ�" << endl;
		Tree.inorderTraverse(); cout << endl;
	}
	else
	{
		cout << "���ҳɹ� " << count << endl;
	}
	return 0;
}