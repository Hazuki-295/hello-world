#include <iostream>
using namespace std;

/* 列表节点模板类（以单链表形式实现） */
template <typename T> struct LNode {
	// 成员
	T data; LNode *next; // 数据域、指针域
	// 构造函数
	LNode() : data(T()), next(nullptr) {}
	LNode(T x) : data(x), next(nullptr) {}
	LNode(T x, LNode *next) : data(x), next(next) {}
};
template <typename T> using LinkList = LNode<T> *; // 单链表(头指针)

/* 链表模板类(不带头结点) */
template <typename T> class List {

private:
	using ElemType = T;
	using LinkList = LinkList<T>;
	using LNode = LNode<T>;

	LinkList L; // L为单链表的头指针(结构指针类型，指向链表的第一个结点)

public:
	// 构造函数
	List() { InitList(); }; // 默认构造一个空链表

	/* 初始化一个空链表 */
	void InitList() {
		L = nullptr;  // 初始为空链表
	}

	/* 头插法，逆向建立单链表 */
	LinkList List_HeadInsert(int n) {
		LNode *s; ElemType temp;
		L = nullptr; // 初始为空链表
		for (int i = 0; i < n; i++) {
			cin >> temp;

			s = new LNode;  // 创建新结点
			s->data = temp;
			s->next = L;    // 将新结点插入表中(指向之前的第一个结点)，且因为在头部插入新结点，
			L = s;          // 每次插入新结点后，需要将它的地址赋值给头指针L
		}
		return L; // 返回头指针
	}

	/* 尾插法，正向建立单链表 */
	LinkList List_TailInsert(int n) {
		ElemType temp;
		L = new LNode;      // 创建第一个结点
		cin >> temp; L->data = temp;
		LNode *s, *r = L;  // r为表尾指针(初始化指向第一个结点)
		for (int i = 0; i < n - 1; i++) { // 插入其余n-1个结点
			cin >> temp;

			s = new LNode;  // 创建新结点
			s->data = temp; // s指向的结点数据域有值，但其指针域未初始化(若有下一个结点，则会被下一轮循环赋予地址，也就是当前位置的下一条语句)
			r->next = s;    // 当前表尾结点的指针域 r->next 内，存放指向新结点的指针
			r = s;          // r指向新的表尾结点(保持r仍为表尾指针)
		}
		r->next = nullptr; // 尾结点指针置空
		return L;          // 返回头指针
	}

	/* 沿着指针链顺序到达每一个结点，求出单链表的表长 */
	int LinkLength() {
		LNode *p = L; int j = 0; // j为计数器
		while (p != nullptr) {   // 从第一个结点开始，统计数据结点的个数
			j++;
			p = p->next;
		}
		return j;
	}

	/* 按序号查找，返回位置x处的链表结点(不带头结点) */
	LNode *GetElem(int x) {
		LNode *p; int j;

		p = L; j = 1; // 初始化，p指向第一个结点(若为空表，则为nullptr)，j为计数器
		//if (x == 0)
			//return L;     // 不存在位序为0的结点
		if (x < 1)
			return nullptr; // 若x无效，则直接返回NULL
		while (p != nullptr && j < x) { // 从第1个结点开始找，直到 p指向第x个元素(j=x) 或 p为空(达到尾结点)
			p = p->next;
			j++;
		}
		return p; // 若找到，则返回第x个结点的指针；若x大于表长，返回NULL
	}

	/* 按值查找，返回值域为给定值e的链表结点 */
	LNode *LocateElem(ElemType e) {
		LNode *p = L; // 从第一个结点开始找
		while (p != nullptr && (p->data != e)) { // 查找 data 域为 e 的结点
			p = p->next;
		}
		return p; // 找到后返回该结点的指针，否则返回NULL
	}

	/* 插入操作，在表L中第x个位置之前插入新的数据元素e */
	bool ListInsert(int x, ElemType e) {
		LNode *p, *s;
		p = GetElem(x - 1); // 查找插入位置的前驱结点
		if (p == nullptr) {   // 插入位置不合法，
			if (x - 1 == 0) { // 或为第一个结点之前
				s = new LNode;     // 创建新结点
				s->data = e;
				s->next = L;       // 新结点指向原先的第一个结点
				L = s;             // 新结点成为第一个结点
				return true;
			}
			else {
				return false;
			}
		}

		s = new LNode;     // 创建新结点
		s->data = e;
		s->next = p->next; // 处理新结点
		p->next = s;       // 原直接前驱指向新结点
		return true;
	}

	/* 删除操作，删除表L中第x个位置的元素，并用e返回删除元素的值 */
	bool ListDelete(int x, ElemType &e) {
		LNode *p, *q;
		p = GetElem(x - 1); // 查找删除位置的前驱结点
		if (p == nullptr || p->next == nullptr) { // 删除位置不合法 或 GetElem得到尾结点(说明想删除不存在的表尾后的结点)
			if (x - 1 == 0) { // 或删除第一个结点
				q = L;        // 令q指向被删除结点
				L = q->next;  // 将*q结点从链中“断开”
				e = q->data;  // 被删除元素的值赋给e
				free(q);      // 释放结点的存储空间
				return true;
			}
			else {
				return false;
			}
		}

		q = p->next;       // 令q指向被删除结点
		p->next = q->next; // 将*q结点从链中“断开”
		e = q->data;       // 被删除元素的值赋给e
		free(q);           // 释放结点的存储空间
		return true;
	}

	/* 输出操作，顺序输出线性表L的所有元素值 */
	void PrintList() {
		LNode *p = L; // 从第一个结点开始输出
		while (p != nullptr) {
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}

	/* 测试用例 */
	void ListTest();
}; // List

template<typename T> void List<T>::ListTest()
{
	cout << "请输入链表结点个数：" << endl;
	int n; cin >> n; cout << '\n';

	cout << "请输入" << n << "个链表元素：\n";
	List_TailInsert(n); // 尾插法初始化链表
	//List_HeadInsert(n); // 头插法初始化链表（逆序链表）


	cout << "\n初始化完成。\n";
	/* 测试代码 */
	cout << "当前链表长度为：\n" << LinkLength() << '\n';
	cout << "当前链表元素为：\n"; PrintList(); cout << "\n\n";

	/* 操作测试 */
	int delete1, insert1; ElemType temp;
	cout << "删除第x个元素："; cin >> delete1;
	ListDelete(delete1, temp);
	/* 测试代码 */
	cout << "当前链表长度为：\n" << LinkLength() << '\n';
	cout << "当前链表元素为：\n"; PrintList(); cout << "\n\n";

	cout << "在第x个元素之前插入元素："; cin >> insert1;
	cout << "插入的元素："; cin >> temp;
	ListInsert(insert1, temp);
	/* 测试代码 */
	cout << "当前链表长度为：\n" << LinkLength() << '\n';
	cout << "当前链表元素为：\n"; PrintList(); cout << "\n\n";
}

int main()
{
	List<int> L;
	L.ListTest();
}
