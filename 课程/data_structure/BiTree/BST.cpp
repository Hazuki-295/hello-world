#include <iostream>
using namespace std;

/* �������Ķ�������洢��ʾ */
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
	BiTNode *searchBST(BiTree T, ElemType key) {
		while (T != nullptr && key != T->data) {   // �����ջ���ڸ����ֵ�������ѭ��
			if (key < T->data)      // С�ڣ������������ϲ���
				T = T->lchild;
			else if (key > T->data) // ���ڣ������������ϲ���
				T = T->rchild;
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
	BiTNode *searchBST(ElemType key) { return searchBST(root, key); }
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
	int val; cin >> val;
	if (Tree.searchBST(val) == nullptr)
	{
		Tree.insertBST(val);
		cout << "����ɹ�" << endl;
		Tree.inorderTraverse(); cout << endl;
	}
	else
	{
		cout << "���ҳɹ� " << endl;
	}
	return 0;
}