#include <iostream>
#include <string>
using namespace std;

#define MaxSize 50 // 线性表的最大长度

struct Staff {
	// 成员
	string name; string position; int id; // 每名员工有姓名、职务、工号等属性
	// 构造函数
	Staff() :name(), position(), id(0) {};

	Staff &operator=(const Staff &temp)
	{
		name = temp.name;
		position = temp.position;
		id = temp.id;
		return *this;
	}
};

istream &operator>>(istream &is, Staff &temp)
{
	is >> temp.name >> temp.position >> temp.id;
	return is;
}

ostream &operator<<(ostream &os, const Staff &temp)
{
	os << temp.name << ' ' << temp.position << ' ' << temp.id;
	return os;
}

/* 顺序列表模板类 */
template <typename T> class List {

private:
	using ElemType = T;

	/* 线性表的顺序存储结构(静态分配) */
	ElemType *data; // 顺序表的元素
	int length;     // 顺序表的当前长度

public:
	// 构造函数
	List() { InitList(); } //默认

	/* 初始化一个空的顺序表(为顺序表分配存储空间) */
	void InitList()
	{
		data = new ElemType[MaxSize];
		length = 0;  // 空表长度为0
	}

	void CreatList(int n)
	{
		length = n; ElemType temp;
		for (int i = 0; i < n; i++)
		{
			cin >> temp;
			data[i] = temp;
		}
	}

	/* 插入操作，在表L中第x个位置之前插入新的数据元素e */
	bool ListInsert(int x, ElemType e)
	{
		if (x<1 || x > length + 1) // 插入的位置非法
			return false;

		if (length >= MaxSize) // 当前存储空间已满，不能插入
			return false;

		ElemType *p, *q;    // p和q为辅助指针 
		q = &(data[x - 1]); // q为插入位置
		for (p = &(data[length - 1]); p >= q; p--) // 插入位置及之后的元素右移
		{
			*(p + 1) = *p;
		}
		*q = e;     // 在插入位置 q 插入新的元素e
		length++; // 表长加1
		return true;
	}

	/* 删除操作，删除表L中第x个位置的元素，并用e返回删除元素的值 */
	bool ListDelete(int x, ElemType &e)
	{
		if (x<1 || x>length) // 删除的位置非法
			return false;

		ElemType *p, *q; // p和q为辅助指针 

		p = &(data[x - 1]);        // p为被删除元素的位置
		e = *p;                    // 被删除元素的值赋给e
		q = &(data[length - 1]);   // 表尾元素的位置
		for (p++; p <= q; p++)     // 被删除元素之后的元素左移
		{
			*(p - 1) = *p;
		}
		length--; // 表长减1
		return true;
	}

	/* 按值查找操作，在表L中查找具有给定关键字(e)值的元素 */
	int LocateElem(ElemType e)
	{
		for (int i = 0; i < length; i++)
			if (data[i] == e)
				return i + 1; // 下标为i的元素值等于e，返回其位序i+1
		return 0;             // 退出循环，说明查找失败(0表示未找到)
	}

	/* 按位查找操作，找到表L中第i个位置的元素，并用e返回其值 */
	bool GetElem(int x, ElemType &e)
	{
		if (x<1 || x>length)
			return false;
		e = data[x - 1]; // 位序为i的元素，其下标为i-1
		return true;
	}

	/* 输出操作，顺序输出线性表L的所有元素值 */
	void PrintList()
	{
		for (int i = 0; i < length; i++)
		{
			cout << data[i] << ' ';
		}
		cout << endl;
	}

	int LinkLength() { return length; };

	void PrintList2();
}; // SqList

template <typename T> void List<T>::PrintList2()
{
	for (int i = 0; i < length; i++)
	{
		cout << data[i] << ' ';
	}
	cout << endl;
}

int main()
{
	int n, m; cin >> n >> m; // n 名员工，m 次操作

	List<Staff> L;  // 请把所有员工建立一个线性表
	L.CreatList(n); // 建立单链表

	char op; int x; Staff temp;
	// 建立离职、入职、查询函数
	// 当有员工离职或入职时，修改线性表，并且根据输出格式中的要求输出
	for (int i = 0; i < m; i++)
	{
		cin >> op >> x;
		switch (op)
		{
		case'1': // 若op = 1,表示线性表中在位置x的员工离职
			if (L.ListDelete(x, temp))
				L.PrintList2();
			else
				cout << -1 << endl;
			break;

		case'2': // 若op = 2, 表示有员工入职，需要将员工置入线性表中的位置x处
				 // 接下来会输入两个字符串和一个正整数代表该员工的name, position, id
			cin >> temp;
			if (L.ListInsert(x, temp))
				L.PrintList2();
			else
				cout << -1 << endl;
			break;

		case'3': // 若op = 3，表示查询位置x处员工的信息
				 // 操作可能有不合法的情况，这时请按要求输出并忽略该操作
			if (L.GetElem(x, temp) == false) // 查询位置x处员工的信息
			{
				cout << -1 << endl;
				continue;
			}
			cout << temp << endl;
			break;

			/* 操作不合法 */
		default:
			cout << -1 << endl;
			break;
		}
	}

	return 0;
}
