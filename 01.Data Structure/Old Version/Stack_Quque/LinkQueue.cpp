#include <iostream>
using namespace std;

/* 列表节点模板类（以单链表形式实现） */
template <typename T> struct ListNode {
	// 成员
	T data; ListNode *next; // 数据域、指针域
	// 构造函数
	ListNode() : data(T()), next(nullptr) {}
	ListNode(T x) : data(x), next(nullptr) {}
	ListNode(T x, ListNode *next) : data(x), next(next) {}
};

/* 链队列模板类 */
template<typename T> class Queue {
private:
	using ElemType = T;
	using ListNode = ListNode<T>;

	/* 队列的链式存储类型 */
	ListNode *front, *rear; // 队列的队头和队尾指针(front将始终指向头结点)

public:
	// 构造函数
	Queue() { InitQueue(); } // 默认

	/* 初始化一个空队列 */
	void InitQueue() {
		front = rear = new ListNode; // 建立头结点
		front->next = nullptr;       // 初始为空
	}

	/* 判队列空 */
	bool QueueEmpty() {
		return rear == front; // 队空条件
	}

	/* 入队，将x加入，使之成为新的队尾 */
	void EnQueue(ElemType x) {
		ListNode *s = new ListNode(x, nullptr); // 创建新结点
		rear->next = s; // 当前的表尾指向新结点
		rear = s;       // 更新表尾指针
	}

	/* 出队，若队列Q非空，删除队头元素，并用x返回 */
	bool DeQueue(ElemType &x) {
		if (rear == front) { // 空队
			return false;
		}
		ListNode *p = front->next; // 令p指向队头元素
		x = p->data;               // 用x返回其值
		front->next = p->next;     // 将出队元素从链中断开
		if (rear == p) {           // 若原队列中只有一个结点，删除后变空
			rear = front;          // 即，令rear指向头结点，以保持空队条件
		}
		delete p;
		return true;
	}

	/* 读队头元素，若队列 Q 非空，则用 x 返回队头元素 。 */
	bool GetHead(ElemType &x) {
		if (rear == front) {   // 空队
			return false;
		}
		ListNode *p = front->next; // 取队头元素
		x = p->data;               // 用x返回其值
		return true;
	}
}; // LinkQueue

int main() {
	Queue<int> Q;

	cout << "请输入队列元素个数：";
	int num; cin >> num;

	cout << "请输入" << num << "个队列元素：";
	int delete1, insert1;
	for (int i = 0; i < num; i++) {
		cin >> insert1;
		Q.EnQueue(insert1);
	}

	/* 取栈顶 */
	int top; Q.GetHead(top);
	cout << "队首元素：" << top << endl;

	/* 出栈测试 */
	cout << "出队元素：\n";
	while (!Q.QueueEmpty()) {
		Q.DeQueue(delete1);
		cout << delete1 << " ";
	}
	cout << endl;
}
