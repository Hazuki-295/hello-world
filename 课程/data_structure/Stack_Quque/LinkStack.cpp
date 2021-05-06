#include <iostream>
using namespace std;

/* ���б�Ϊ���࣬������ջģ���� */
template <typename T> class Stack : public List<T> { //���б����/ĩ����Ϊջ��/��

private:
	typedef T ElemType;

public:
	// ���캯��
	Stack() { InitStack(); } //Ĭ��

	/* ��ʼ��һ����ջ */
	void InitStack() {}

	/* ��ջ�� */
	bool StackEmpty() { return List<T>::LinkLength() == 0; }

	/* ��ջ����ջSδ������x����ʹ֮��Ϊ�µ�ջ�� */
	bool Push(ElemType x)
	{
		return List<T>::ListInsert(List<T>::LinkLength() + 1, x);
	}

	/* ��ջ����ջS�ǿգ��򵯳�ջ��Ԫ�أ�����x������ֵ */
	bool Pop(ElemType &x)
	{
		return List<T>::ListDelete(List<T>::LinkLength(), x);
	}
}; // Stack