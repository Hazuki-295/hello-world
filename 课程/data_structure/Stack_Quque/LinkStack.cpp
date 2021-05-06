#include <iostream>
using namespace std;

#include "../List/LinkList.cpp"

/* ���б�Ϊ���࣬������ջģ���� */
template <typename T> class Stack : public List<T> { //���б����/ĩ����Ϊջ��/��

private:
	typedef T ElemType;

public:
	// ���캯��
	Stack() { InitStack(); } //Ĭ��

	/* ��ʼ��һ����ջ */
	void InitStack() { List<T>::InitList(); }

	/* ��ջ�� */
	bool StackEmpty() { return List<T>::LinkLength() == 0; }

	/* ��ջ����x����ʹ֮��Ϊ�µ�ջ�� */
	bool Push(ElemType x)
	{
		return List<T>::ListInsert(List<T>::LinkLength() + 1, x);
	}

	/* ��ջ������ջ��Ԫ�أ�����x������ֵ */
	bool Pop(ElemType &x)
	{
		return List<T>::ListDelete(List<T>::LinkLength(), x);
	}
}; // Stack

int main()
{
	int n, temp;

	Stack<int> L;

	cout << "�����������������\n";
	cin >> n; cout << '\n';

	cout << "������" << n << "������Ԫ�أ�\n";
	L.List_TailInsert(n); //��ʼ������


	cout << "\n��ʼ����ɡ�\n";
	/* ���Դ��� */
	cout << "��ǰ������Ϊ��\n" << L.LinkLength() << '\n';
	cout << "��ǰ����Ԫ��Ϊ��\n"; L.PrintList(); cout << "\n\n";

	int delete1, insert1;
	int index;

	while (true)
	{
		/* ��ջ���� */
		cout << "��ջ��\n";
		cin >> insert1;
		L.Push(insert1);
		/* ���Դ��� */
		cout << "��ǰ������Ϊ��\n" << L.LinkLength() << '\n';
		cout << "��ǰ����Ԫ��Ϊ��\n"; L.PrintList(); cout << "\n\n";
	}

	while (!L.StackEmpty())
	{
		/* ��ջ���� */
		cout << "��ջ��\n";
		L.Pop(delete1);
		/* ���Դ��� */
		cout << "��ǰ������Ϊ��\n" << L.LinkLength() << '\n';
		cout << "��ǰ����Ԫ��Ϊ��\n"; L.PrintList(); cout << "\n\n";
	}

}