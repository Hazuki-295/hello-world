#include <iostream>
using namespace std;

/* 以列表为基类，派生出栈模板类 */
template <typename T> class Stack : public List<T> { //将列表的首/末端作为栈顶/底

private:
	typedef T ElemType;

public:
	// 构造函数
	Stack() { InitStack(); } //默认

	/* 初始化一个空栈 */
	void InitStack() {}

	/* 判栈空 */
	bool StackEmpty() { return List<T>::LinkLength() == 0; }

	/* 进栈，若栈S未满，则将x加入使之成为新的栈顶 */
	bool Push(ElemType x)
	{
		return List<T>::ListInsert(List<T>::LinkLength() + 1, x);
	}

	/* 出栈，若栈S非空，则弹出栈顶元素，并用x返回其值 */
	bool Pop(ElemType &x)
	{
		return List<T>::ListDelete(List<T>::LinkLength(), x);
	}
}; // Stack