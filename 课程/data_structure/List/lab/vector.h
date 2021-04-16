/*************************************************************************************
* 问题描述：某软件公司大约有30名员工，每名员工有姓名、工号、职务等属性，每年都有员工离职和入职。
* 把所有员工建立一个线性表，建立离职和入职函数，当有员工离职或入职时，修改线性表，并且显示最新的员工名单。
* 题目要求:
* 1)	顺序表存储,实现顺序表的插入、删除、查找、输出等基本操作；调用基本操作完成。
* 2)  链表存储,实现链表的插入、删除、查找、输出等基本操作；调用基本操作完成。
* 
* 注意: 需要使用c++11 或以上版本
* Description: 数据结构实验1
*************************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

/* Employee 用于保存员工信息的结构体 */
struct Employee {
    string name; /*!< 员工姓名 */
    string position; /*!< 员工职务 */
    int id; /*!< 员工编号 */

    Employee();
    Employee(const string &n, const string &p, int id);
    string toString() const;
};

/* 构造函数 创建姓名职位为空，编号为-1的员工 */
Employee::Employee() : name(""), position(""), id(-1) {
}
/* 构造函数 创建姓名为n，职位为p，编号为id的员工*/
Employee::Employee(const string &n, const string &p, int id) :
    name(n), position(p), id(id) {
}

/*
 * Function: toString
 * Description: 将员工信息转化为字符串
 * Input: 无
 * Output: string 代表员工信息的字符串
 */
string Employee::toString() const {
    return "{" + name + ", " + position + ", " + to_string(id) + "}";
}

/* 定义两员工相等为 姓名，职位，编号同时相等 */
bool operator ==(const Employee &a, const Employee &b) {
    return (a.name == b.name && a.position == b.position && a.id == b.id);
}


/* Vector 用于保存所有员工信息的 "线性表" */
struct Vector {
    size_t size; /*<! 员工人数 */
    size_t length; /*<! 数组长度 */
    Employee *array; /*<! 用于保存员工信息的数组 */
    Vector();
    Vector(size_t l);
    ~Vector();

    void expansion();
    bool insert(int x, Employee e);
    bool erase(int x);
    const Employee *find(int x);
    void print();
};

/* 构造函数 默认创建长度为32的线性表 */
Vector::Vector() : size(0), length(32) {
    array = new Employee[32];
}
/* 构造函数 创建长度为l的线性表*/
Vector::Vector(size_t l) : size(0), length(l) {
    array = new Employee[l];
}

Vector::~Vector() {
    delete[] array;
}

/*
 * Function: expansion
 * Description: 扩张数组，当员工数量超过数组长度时，将数组扩张为原来的2倍，
 *              从而实现动态可变长数组，通过势能分析可知，扩张的时间复杂度
 *              均摊O(1)
 * Input: 无
 * Output: 无
 */
void Vector::expansion() {
    Employee *narray = new Employee[length * 2];
    for (int i = 0; i < length; i++)
        narray[i] = array[i];
    delete[] array;
    array = narray;
    length <<= 1;
}

/*
 * Function: insert
 * Description: 向线性表中位置x处添加一位员工数据
 * Input: x(int)插入位置, e(Employee) 代表一名员工
 * Output: (bool) ture: 插入成功， false：插入失败
 */
bool Vector::insert(int x, Employee e) { //    插入
    --x;
    if (x < 0 || x > size)
        return false;
    if (size >= length)
        expansion();
    size += 1;
    for (int i = size - 1; i - 1 >= x; i--)
        array[i] = array[i - 1];
    array[x] = e;
    return true;
}

/*
 * Function: erase
 * Description: 从线性表中删除位置x处员工数据
 * Input: x(int)删除位置, e(Employee) 代表一名员工
 * Output: (bool) ture: 删除成功， false: 删除失败
 */
bool Vector::erase(int x) { //        删除
    --x;
    if (x < 0 || x >= size)
        return false;
    for (size_t i = x; i + 1 < size; i++)
        array[i] = array[i + 1];
    --size;
    return true;
}

/*
 * Function: find
 * Description: 查找位置x处的员工
 * Input: x(int) 查找位置
 * Output: (Employee*) 员工指针
 */
const Employee *Vector::find(int x) { //         查找
    --x;
    if (x < 0 || x >= size)
        return NULL;
    return (const Employee *)(array + x);
}

/*
 * Function: print
 * Description: 打印所有员工的信息
 * Input: 无
 * Output: 无
 */
void Vector::print() {  //                 输出
    for (size_t i = 0; i < size; i++)
        cout << array[i].toString() << " ";
    cout << endl;
}

/* ListNode 链表结点 用于在链表中存储一名员工 */
struct ListNode {
    Employee e; /*<! 员工信息 */
    ListNode *next; /*<! 链表指针 */

    ListNode();
    ListNode(Employee e);
};

/* 构造函数 创建一个包含默认员工信息的链表结点 */
ListNode::ListNode() : next(NULL) {
    e = Employee();
}
/* 创建一个 包含员工信息e 的链表结点*/
ListNode::ListNode(Employee e) : e(e), next(NULL) {
}

/* List 用于保存所有员工信息的链表 */
struct List {
    size_t size;
    ListNode *head;
    List();
    ~List();
    bool insert(int x, Employee e);
    bool erase(int x);
    const Employee *find(int x);
    void print();
};

/* 构造函数 创建一个空链表 */
List::List() : size(0) {
    head = new ListNode();
}
List::~List() {
    ListNode *p = head;
    do {
        ListNode *np = p->next;
        delete p;
        p = np;
    } while (p != NULL);
}

/*
 * Function: insert
 * Description: 向线性表中位置x处添加一位员工数据
 * Input: x(int)插入位置, e(Employee) 代表一名员工
 * Output: (bool) ture: 插入成功， false：插入失败
 */
bool List::insert(int x, Employee e) {  //           插入
    --x;
    if (x < 0 || x > size)
        return false;
    ListNode *cur = new ListNode(e), *p = head;
    while (x--)
        p = p->next;
    if (p != NULL)
        cur->next = p->next;
    p->next = cur;
    return true;
}

/*
 * Function: erase
 * Description: 从线性表中删除位置x处员工数据
 * Input: x(int)删除位置, e(Employee) 代表一名员工
 * Output: (bool) ture: 删除成功， false: 删除失败
 */
bool List::erase(int x) {  //           删除
    if (x < 0 || x >= size)
        return false;
    ListNode *p = head;
    while (x--)
        p = p->next;
    ListNode *q = p->next;
    p->next = q->next;
    delete q;
    return true;
}

/*
 * Function: find
 * Description: 查找位置x处的员工
 * Input: x(int) 查找位置
 * Output: (Employee*) 员工指针
 */
const Employee *List::find(int x) {  //          查找
    --x;
    if (x < 0 || x >= size)
        return NULL;
    ListNode *p = head;
    while (--x)
        p = p->next;
    return (const Employee *)(&(p->next->e));
}

/*
 * Function: print
 * Description: 打印所有员工的信息
 * Input: 无
 * Output: 无
 */
void List::print() {  //                   输出
    for (ListNode *p = head->next; p != NULL; p = p->next) {
        cout << p->e.toString() << " ";
    }
    cout << endl;
}

bool manage()
{
    /*	ios::sync_with_stdio(false); cin.tie(0);*/
    freopen("text10.in", "r", stdin);
    freopen("text10.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    Vector vec(n);
    for (int i = 0; i < n; i++) {
        Employee e;
        cin >> e.name >> e.position >> e.id;
        vec.insert(i + 1, e);
    }

    int op, x;
    for (int i = 0; i < m; i++)
    {
        cin >> op >> x;

        if (op == 1) {
            if (vec.erase(x))
                vec.print();
            else
                cout << -1 << endl;
        }
        else if (op == 2) {
            Employee e;
            cin >> e.name >> e.position >> e.id;
            if (vec.insert(x, e))
                vec.print();
            else
                cout << -1 << endl;
        }
        else {
            const Employee *ptr = vec.find(x);
            if (ptr != NULL)
                cout << ptr->toString() << endl;
            else
                cout << -1 << endl;
        }
    }
    return true;
}