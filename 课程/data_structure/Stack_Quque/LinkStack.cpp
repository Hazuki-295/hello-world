#include <iostream>
using namespace std;

#include "../List/LinkList.cpp"

/* 以列表为基类，派生出栈模板类 */
template <typename T> class Stack : public List<T> { //将列表的首/末端作为栈顶/底

private:
	typedef T ElemType;

public:
	// 构造函数
	Stack() { InitStack(); } //默认

	/* 初始化一个空栈 */
	void InitStack() { List<T>::InitList(); }

	/* 判栈空 */
	bool StackEmpty() { return List<T>::LinkLength() == 0; }

	/* 进栈，将x加入使之成为新的栈顶 */
	bool Push(ElemType x)
	{
		return List<T>::ListInsert(List<T>::LinkLength() + 1, x);
	}

	/* 出栈，弹出栈顶元素，并用x返回其值 */
	bool Pop(ElemType &x)
	{
		return List<T>::ListDelete(List<T>::LinkLength(), x);
	}
}; // Stack

int main()
{
	int n, temp;

	Stack<int> L;

	cout << "请输入链表结点个数：\n";
	cin >> n; cout << '\n';

	cout << "请输入" << n << "个链表元素：\n";
	L.List_TailInsert(n); //初始化链表


	cout << "\n初始化完成。\n";
	/* 测试代码 */
	cout << "当前链表长度为：\n" << L.LinkLength() << '\n';
	cout << "当前链表元素为：\n"; L.PrintList(); cout << "\n\n";

	int delete1, insert1;

	while (true)
	{
		/* 入栈测试 */
		cout << "入栈：\n";
		cin >> insert1;
		L.Push(insert1);
		/* 测试代码 */
		cout << "当前链表长度为：\n" << L.LinkLength() << '\n';
		cout << "当前链表元素为：\n"; L.PrintList(); cout << "\n\n";
	}

	while (!L.StackEmpty())
	{
		/* 出栈测试 */
		cout << "出栈。\n";
		L.Pop(delete1);
		/* 测试代码 */
		cout << "当前链表长度为：\n" << L.LinkLength() << '\n';
		cout << "当前链表元素为：\n"; L.PrintList(); cout << "\n\n";
	}

}
