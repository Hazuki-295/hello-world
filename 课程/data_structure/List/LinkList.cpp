#include <iostream>

using namespace std;

/* 列表节点模板类（以单链表形式实现） */
template <typename T> struct ListNode {
	// 成员
	T data; ListNode *next; // 数据域、指针域
	// 构造函数
	ListNode() : data(0), next(nullptr) {}
	ListNode(int x) : data(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : data(x), next(next) {}
};

template <typename T> using LinkList = ListNode<T> *; // 单链表(头指针)

/* 链表模板类 */
template <typename T> class List {

private:
	using ElemType = T;
	using LinkList = LinkList<T>;
	using ListNode = ListNode<T>;

	LinkList L; // L为单链表的头指针(结构指针类型，指向链表的第一个结点)

public:
	// 构造函数
	List() { InitList(); }; // 默认构造一个空链表

	/* 初始化一个空链表 */
	void InitList() // 默认构造一个空链表
	{
		L = (LinkList)malloc(sizeof(ListNode));  // 创建头结点
		L->next = nullptr;                    // 初始为空链表
	}

	/* 头插法，逆向建立单链表 */
	LinkList List_HeadInsert(int n)
	{
		ListNode *s; ElemType temp;
		L = (LinkList)malloc(sizeof(ListNode));  // 创建头结点
		L->next = nullptr;                    // 初始为空链表
		for (int i = 0; i < n; i++)
		{
			cin >> temp;

			s = (ListNode *)malloc(sizeof(ListNode)); // 创建新结点
			s->data = temp;
			s->next = L->next; // 将新结点插入表中
			L->next = s;       // 每次将s所指结点插在最前端
		}
		return L; // 返回头指针
		return L; // 返回头指针
	}

	/* 尾插法，正向建立单链表 */
	LinkList List_TailInsert(int n)
	{
		ElemType temp;
		L = (LinkList)malloc(sizeof(ListNode)); // 创建头结点
		ListNode *s, *r = L;  // r为表尾指针(初始化指向头结点)
		for (int i = 0; i < n; i++)
		{
			cin >> temp;

			s = (ListNode *)malloc(sizeof(ListNode)); // 创建新结点
			s->data = temp; // s结构指针有数据域，但其指针域未初始化(若有下一个结点，则会被下一轮循环赋予地址，也就是当前位置的下一条语句)
			r->next = s;    // 当前表尾结点的指针域 r->next 内，存放指向新结点的指针
			r = s;          // r指向新的表尾结点(保持r仍为表尾指针)
		}
		r->next = nullptr; // 尾结点指针置空
		return L;          // 返回头指针
	}

	/* 求单链表表长 */
	int LinkLength()
	{
		ListNode *p = L->next; int j = 0; // j为计数器
		while (p != nullptr) // 从第一个结点开始，计数据结点的个数
		{
			j++;
			p = p->next;
		}
		return j;
	}

	/* 按序号查找 */
	ListNode *GetElem(int x) // L为"带头结点"的单链表的头指针
	{
		ListNode *p; int j;

		p = L->next; j = 1; // 初始化，p指向第一个结点，j为计数器

		if (x == 0)
			return L;       // 若x等于0，则返回头结点
		if (x < 1)
			return nullptr; // 若x无效，则直接返回NULL
		while (p != nullptr && j < x)  // 从第1个结点开始找，直到 p指向第x个元素(j=x) 或 p为空(达到尾结点)
		{
			p = p->next;
			j++;
		}
		return p; // 若找到，则返回第x个结点的指针；若x大于表长，返回NULL
	}

	/* 按值查找 */
	ListNode *LocateElem(ElemType e)
	{
		ListNode *p = L->next;
		while (p != nullptr && (p->data != e)) // 从第1个结点开始查找 data域为e 的结点
		{
			p = p->next;
		}
		return p; // 找到后返回该结点的指针，否则返回NULL
	}

	/* 插入操作，在表L中第x个位置之前插入新的数据元素e */
	bool ListInsert(int x, ElemType e)
	{
		ListNode *p, *s;
		p = GetElem(x - 1); // 查找插入位置的前驱结点
		if (!p) // 插入位置不合法
			return false;

		s = (ListNode *)malloc(sizeof(ListNode)); // 创建新结点
		s->data = e;
		s->next = p->next; // 处理新结点
		p->next = s;       // 原直接前驱指向新结点
		return true;
	}

	/* 删除操作，删除表L中第x个位置的元素，并用e返回删除元素的值 */
	bool ListDelete(int x, ElemType &e)
	{
		ListNode *p, *q;
		p = GetElem(x - 1); // 查找删除位置的前驱结点
		if (!p || p->next == nullptr) // 删除位置不合法 或 GetElem得到尾结点
			return false;

		q = p->next;       // 令q指向被删除结点
		p->next = q->next; // 将*q结点从链中“断开”
		e = q->data;       // 被删除元素的值赋给e
		free(q);           // 释放结点的存储空间
		return true;
	}

	/* 输出操作，顺序输出线性表L的所有元素值 */
	void PrintList()
	{
		ListNode *p = L->next; // 从第一个结点开始输出
		while (p != nullptr)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
}; // List
