#pragma once

typedef int ElemType;

#include <iostream>
using namespace std;

/* 单链表存储结构 */
typedef struct Lnode {

	ElemType data; // 数据域
	struct Lnode *next; // 指针域(结构指针)

} Lnode, *LinkList;

/* 头插法：逆向建立单链表 */
LinkList List_HeadInsert(LinkList &L, int n) 
{
	LinkList s; ElemType temp;
	L = (LinkList)malloc(sizeof(Lnode)); // 创建头结点
	L->next = nullptr;                   // 初始为空链表
	for (int i = 0; i < n; i++)
	{
		cin >> temp;

		s = (LinkList)malloc(sizeof(Lnode)); // 创建新结点
		s->data = temp;
		s->next = L->next;
		L->next = s; // 每次将s所指结点插在最前端
	}
	return L; // 返回头指针
}

/* 尾插法：正向建立单链表 */
LinkList List_TailInsert(LinkList &L, int n)
{
	ElemType temp;
	L = (LinkList)malloc(sizeof(Lnode)); // 创建头结点
	LinkList s, r = L;  // r为表尾指针(初始化指向头结点)
	for (int i = 0; i < n; i++)
	{
		cin >> temp;

		s = (LinkList)malloc(sizeof(Lnode));
		s->data = temp;					 // s结构指针有数据域，但其指针域未初始化(若有下一个结点，则会被下一轮循环赋予地址，也就是当前位置的下一条语句)
		r->next = s;					 // r->next："当前表尾结点"的指针域内，存放指向新结点的指针
		r = s;							 // r指向新的表尾结点(保持r仍为表尾指针)

		/* 实际上，r和s都只是中间变量，信息最终是保存在真实的结点(与指针无关)中的。 */
		/* 新节点，是放在内存当中的，这个东西只有一份儿。但是你可以弄100个指针变量，都指向这个地址。 */
		/* 你要做的工作不是管这些变量如何如何，而是让节点上的那个next指针，指向下一个内存块(新的结点)。 */
	}
	r->next = nullptr;					 // 尾结点指针置空
	return L;
}

int LinkLength(LinkList L)
{
	LinkList p = L->next; int j = 0; // j为计数器
	while (p != nullptr)             // 从第一个结点开始，计算数据结点的个数
	{
		j++;
		p = p->next;
	}
	return j;
}

/* 按序号查找结点 */
LinkList GetElem(LinkList L, int x)
{	//L为"带头结点"的单链表的头指针
	LinkList p; int j;

	p = L->next; j = 1; //初始化：p指向第一个结点，j为计数器

	if (x == 0)
		return L; //若x等于0，则返回头结点
	if (x < 1)
		return nullptr; //若x无效，则返回NULL
	while (p != nullptr && j < x)  //从第1个结点开始找，直到p指向第x个元素 或 p为空(达到尾结点)
	{
		p = p->next;
		j++;
	}
	return p; //若找到，则返回第x个结点的指针；若x大于表长，返回NULL
}

/* 按值查找表结点 */
LinkList LocateElem(LinkList L, int e)
{
	LinkList p = L->next;
	while (p != nullptr && (p->data != e)) //从第1个结点开始查找data域为e的结点
	{
		p = p->next;
	}
	return p; //找到后返回该结点的指针，否则返回NULL
}

bool ListInsert(LinkList L, int x, ElemType e)
{	//在"带头结点"的单链表L中，第x个位置之前插入元素e
	LinkList p, s;
	p = GetElem(L, x - 1); //查找插入位置的前驱结点
	if (!p)
	{
		return false;
	}
	s = (LinkList)malloc(sizeof(Lnode)); //申请一个新结点
	s->data = e; 
	s->next = p->next; //处理新结点
	p->next = s; //原直接前驱指向新结点
	return true;
}

bool ListDelete(LinkList L, int x)
{	//在"带头结点"的单链表L中，删除第x个元素
	LinkList p, q;
	p = GetElem(L, x - 1); //查找删除位置的前驱结点
	if (!p)
	{
		return false;
	}
	q = p->next;		   //令q指向被删除结点
	p->next = q->next;	   //将*q结点从链中“断开”
	free(q);			   //释放结点的存储空间
	return true;
}

bool PrintList(LinkList L)
{
	LinkList p = L->next; //从第一个结点开始输出
	while (p != nullptr)
	{
		cout << p->data << endl;
		p = p->next;
	}
	cout << endl;
	return true;
}