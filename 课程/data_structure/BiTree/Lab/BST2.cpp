#include <iostream>
#include <queue>
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

template<typename ElemType> class BST
{
private:
	using BiTNode = ::BiTNode<ElemType>;
	using BiTree = ::BiTree<ElemType>;

	BiTree root = nullptr; // ָ��������ָ��

public:
	queue<int> print; // ���ڴ���������

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
	void visit(ElemType &e) { print.push(e); }

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

/* �������汾��ͬ��ƽ̨�Ͽ�ͨ���汾 */
int main()
{
	int nodeNum; cin >> nodeNum;
	BST<int> Tree; Tree.creatBST(nodeNum);
	Tree.inorderTraverse(); // �������ԭ���������������������
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
		cout << "����ɹ�" << endl;
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
		cout << "���ҳɹ� " << count << endl;
	}
	return 0;
}
