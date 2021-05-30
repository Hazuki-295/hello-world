#include <iostream>
#include <string>
using namespace std;

struct Staff { string name; string position; int id; }; // 每名员工有姓名、职务、工号等属性




/* 单链表存储结构 */
typedef struct Lnode {

	node data; //数据域
	struct Lnode *next; //指针域(结构指针)

} Lnode, *LinkList;

/* 尾插法：正向建立单链表 */
LinkList List_TailInsert(LinkList &L, int n)
{
	node temp;
	L = (LinkList)malloc(sizeof(Lnode)); //创建头结点
	LinkList s, r = L;  //r为表尾指针(初始化指向头结点)
	for (int i = 0; i < n; i++)
	{
		cin >> temp.name >> temp.position >> temp.id;

		s = (LinkList)malloc(sizeof(Lnode));
		s->data = temp;
		r->next = s;
		r = s;							 //r指向新的表尾结点(保持r仍为表尾指针)
	}
	r->next = nullptr;					 //尾结点指针置空
	return L;
}

int LinkLength(LinkList L)
{
	LinkList p = L->next; int j = 0;
	while (p != nullptr) //从第一个结点开始，计算数据结点的个数
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

bool ListInsert(LinkList L, int x, node e)
{	//在"带头结点"的单链表L中，第x个位置之前插入元素e
	LinkList p, s;
	p = GetElem(L, x - 1); //查找插入位置的前驱结点
	if (!p)
	{
		cout << -1 << endl;
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
		cout << -1 << endl;
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
		cout << p->data.name << ' ' << p->data.position << ' ' << p->data.id << ' ';
		p = p->next;
	}
	cout << endl;
	return true;
}

int main()
{
	int n, m;//初始n名员工，现在该公司还有m次操作
	cin >> n >> m;

	LinkList L; //创建链表头指针

	List_TailInsert(L, n); //初始化链表

	char op; int x;

	for (int i = 0; i < m; i++)
	{
		cin >> op >> x;
		switch (op)
		{
		case'1':
			if (ListDelete(L, x))//线性表中在位置x的员工离职
				PrintList(L);
			break;

		case'2':
			node temp;
			cin >> temp.name >> temp.position >> temp.id;
			if (ListInsert(L, x, temp))//有员工入职，需要将员工置入线性表中的位置x处
				PrintList(L);
			break;

		case'3':
			if (x == 0)
			{
				cout << -1 << endl;
				break;
			}
			LinkList p;
			p = GetElem(L, x);//查询位置x处员工的信息
			if (!p)
			{
				cout << -1 << endl;
				break;
			}
			cout << p->data.name << ' ' << p->data.position << ' ' << p->data.id << endl;
			break;

			/* 操作不合法 */
		default:
			cout << -1 << endl;
			break;
		}
	}

	return 0;
}
