#include <iostream>
using namespace std;

#include "../List/LinkList.cpp"

/* 以列表为基类，派生出栈模板类 */
template <typename T> class Stack : public List<T> { // 将列表的首/末端作为栈顶/底
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
	bool Push(ElemType x) {
		return List<T>::ListInsert(List<T>::LinkLength() + 1, x); // 在表尾插入
	}

	/* 出栈，弹出栈顶元素，并用x返回其值 */
	bool Pop(ElemType &x) {
		return List<T>::ListDelete(List<T>::LinkLength(), x); // 表尾元素删除
	}

	/* 读栈顶元素，若栈非空，则用x返回栈顶元素 */
	bool GetTop(ElemType &x) {
		auto p = List<T>::GetElem(List<T>::LinkLength()); // 取表尾元素
		if (p != nullptr) {
			x = p->data;
			return true;
		}
		return false;
	}
}; // Stack

int main() {
	Stack<int> S; S.InitStack();

	cout << "请输入入栈元素个数：";
	int num; cin >> num;

	cout << "请输入" << num << "个入栈元素：";
	int delete1, insert1;
	for (int i = 0; i < num; i++) {
		cin >> insert1;
		S.Push(insert1);
	}

	/* 取栈顶 */
	int top; S.GetTop(top);
	cout << "栈顶元素：" << top << endl;

	/* 出栈测试 */
	cout << "出栈元素：\n";
	while (!S.StackEmpty()) {
		S.Pop(delete1);
		cout << delete1 << " ";
	}
	cout << endl;
}