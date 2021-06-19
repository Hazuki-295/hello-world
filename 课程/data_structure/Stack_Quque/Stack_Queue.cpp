#include <iostream>
using namespace std;

#define MAXSIZE 50

/* 顺序栈模板类 */
template<typename T> class Stack {
private:
	using ElemType = T;

	/* 栈的顺序存储类型 */
	ElemType *data;     // 存放栈中元素
	int top;            // 栈顶指针

	int MaxSize;        // 栈中元素的最大个数

public:
	// 构造函数
	Stack(int size = MAXSIZE) :MaxSize(size) { InitStack(); } //默认

	/* 初始化一个空栈 */
	void InitStack() {
		top = -1; // 初始化栈顶指针
		data = new ElemType[MaxSize]; // 数据域
	}

	/* 判栈空 */
	bool StackEmpty() {
		return top == -1;
	}

	/* 进栈，若栈S未满，则将x加入使之成为新的栈顶 */
	bool Push(ElemType x) {
		if (top == MaxSize - 1) { // 栈满，报错
			return false;
		}
		data[++top] = x; // 指针先加1，再入栈
		return true;
	}

	/* 出栈，若栈S非空，则弹出栈顶元素，并用x返回其值 */
	bool Pop(ElemType &x) {
		if (top == -1) {  // 栈空，报错
			return false;
		}
		x = data[top--];  // 先出栈，指针再减1
		return true;
	}

	/* 读栈顶元素 */
	bool GetTop(ElemType &x) {
		if (top == -1) {   // 栈空，报错
			return false;
		}
		x = data[top];     // x记录栈顶元素
		return true;
	}
}; // SqStack

/* 顺序队列模板类 */
template<typename T> class Queue {

private:
	using ElemType = T;

	/* 队列的顺序存储类型 */
	ElemType *data;      // 存放队列元素
	int front, rear;     // 队头指针和队尾指针

	int maxsize;	     // 队列的最大元素个数

public:
	// 构造函数
	Queue() { InitQueue(); } //默认

	/* 初始化一个空队列 */
	void InitQueue()
	{
		rear = front = 0;			  // 初始化队首、队尾指针

		maxsize = MaxSize;
		data = new ElemType[maxsize]; // 数据域
	}

	/* 初始化一个空队列(指定大小) */
	void InitQueue(int size)
	{
		rear = front = 0;			  // 初始化队首、队尾指针

		maxsize = size;
		data = new ElemType[maxsize]; // 数据域
	}

	/* 判队列空 */
	bool QueueEmpty()
	{
		if (rear == front) //队空条件
			return true;
		else
			return false;
	}

	/* 入队，若队列Q未满，将x加入，使之成为新的队尾 */
	bool EnQueue(ElemType x)
	{
		if ((rear + 1) % maxsize == front) // 队满则报错
			return false;
		data[rear] = x;
		rear = (rear + 1) % maxsize; // 队尾指针加1取模
		return true;
	}

	/* 出队，若队列Q非空，删除队头元素，并用x返回 */
	bool DeQueue(ElemType &x)
	{
		if (rear == front) // 队空则报错
			return false;
		x = data[front];
		front = (front + 1) % maxsize; // 队头指针加1取模
		return true;
	}
}; // SqQueue
