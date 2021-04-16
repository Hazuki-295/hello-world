/*************************************************************************************
* ����������ĳ�����˾��Լ��30��Ա����ÿ��Ա�������������š�ְ������ԣ�ÿ�궼��Ա����ְ����ְ��
* ������Ա������һ�����Ա�������ְ����ְ����������Ա����ְ����ְʱ���޸����Ա�������ʾ���µ�Ա��������
* ��ĿҪ��:
* 1)	˳���洢,ʵ��˳���Ĳ��롢ɾ�������ҡ�����Ȼ������������û���������ɡ�
* 2)  ����洢,ʵ������Ĳ��롢ɾ�������ҡ�����Ȼ������������û���������ɡ�
* 
* ע��: ��Ҫʹ��c++11 �����ϰ汾
* Description: ���ݽṹʵ��1
*************************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

/* Employee ���ڱ���Ա����Ϣ�Ľṹ�� */
struct Employee {
    string name; /*!< Ա������ */
    string position; /*!< Ա��ְ�� */
    int id; /*!< Ա����� */

    Employee();
    Employee(const string &n, const string &p, int id);
    string toString() const;
};

/* ���캯�� ��������ְλΪ�գ����Ϊ-1��Ա�� */
Employee::Employee() : name(""), position(""), id(-1) {
}
/* ���캯�� ��������Ϊn��ְλΪp�����Ϊid��Ա��*/
Employee::Employee(const string &n, const string &p, int id) :
    name(n), position(p), id(id) {
}

/*
 * Function: toString
 * Description: ��Ա����Ϣת��Ϊ�ַ���
 * Input: ��
 * Output: string ����Ա����Ϣ���ַ���
 */
string Employee::toString() const {
    return "{" + name + ", " + position + ", " + to_string(id) + "}";
}

/* ������Ա�����Ϊ ������ְλ�����ͬʱ��� */
bool operator ==(const Employee &a, const Employee &b) {
    return (a.name == b.name && a.position == b.position && a.id == b.id);
}


/* Vector ���ڱ�������Ա����Ϣ�� "���Ա�" */
struct Vector {
    size_t size; /*<! Ա������ */
    size_t length; /*<! ���鳤�� */
    Employee *array; /*<! ���ڱ���Ա����Ϣ������ */
    Vector();
    Vector(size_t l);
    ~Vector();

    void expansion();
    bool insert(int x, Employee e);
    bool erase(int x);
    const Employee *find(int x);
    void print();
};

/* ���캯�� Ĭ�ϴ�������Ϊ32�����Ա� */
Vector::Vector() : size(0), length(32) {
    array = new Employee[32];
}
/* ���캯�� ��������Ϊl�����Ա�*/
Vector::Vector(size_t l) : size(0), length(l) {
    array = new Employee[l];
}

Vector::~Vector() {
    delete[] array;
}

/*
 * Function: expansion
 * Description: �������飬��Ա�������������鳤��ʱ������������Ϊԭ����2����
 *              �Ӷ�ʵ�ֶ�̬�ɱ䳤���飬ͨ�����ܷ�����֪�����ŵ�ʱ�临�Ӷ�
 *              ��̯O(1)
 * Input: ��
 * Output: ��
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
 * Description: �����Ա���λ��x�����һλԱ������
 * Input: x(int)����λ��, e(Employee) ����һ��Ա��
 * Output: (bool) ture: ����ɹ��� false������ʧ��
 */
bool Vector::insert(int x, Employee e) { //    ����
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
 * Description: �����Ա���ɾ��λ��x��Ա������
 * Input: x(int)ɾ��λ��, e(Employee) ����һ��Ա��
 * Output: (bool) ture: ɾ���ɹ��� false: ɾ��ʧ��
 */
bool Vector::erase(int x) { //        ɾ��
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
 * Description: ����λ��x����Ա��
 * Input: x(int) ����λ��
 * Output: (Employee*) Ա��ָ��
 */
const Employee *Vector::find(int x) { //         ����
    --x;
    if (x < 0 || x >= size)
        return NULL;
    return (const Employee *)(array + x);
}

/*
 * Function: print
 * Description: ��ӡ����Ա������Ϣ
 * Input: ��
 * Output: ��
 */
void Vector::print() {  //                 ���
    for (size_t i = 0; i < size; i++)
        cout << array[i].toString() << " ";
    cout << endl;
}

/* ListNode ������ �����������д洢һ��Ա�� */
struct ListNode {
    Employee e; /*<! Ա����Ϣ */
    ListNode *next; /*<! ����ָ�� */

    ListNode();
    ListNode(Employee e);
};

/* ���캯�� ����һ������Ĭ��Ա����Ϣ�������� */
ListNode::ListNode() : next(NULL) {
    e = Employee();
}
/* ����һ�� ����Ա����Ϣe ��������*/
ListNode::ListNode(Employee e) : e(e), next(NULL) {
}

/* List ���ڱ�������Ա����Ϣ������ */
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

/* ���캯�� ����һ�������� */
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
 * Description: �����Ա���λ��x�����һλԱ������
 * Input: x(int)����λ��, e(Employee) ����һ��Ա��
 * Output: (bool) ture: ����ɹ��� false������ʧ��
 */
bool List::insert(int x, Employee e) {  //           ����
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
 * Description: �����Ա���ɾ��λ��x��Ա������
 * Input: x(int)ɾ��λ��, e(Employee) ����һ��Ա��
 * Output: (bool) ture: ɾ���ɹ��� false: ɾ��ʧ��
 */
bool List::erase(int x) {  //           ɾ��
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
 * Description: ����λ��x����Ա��
 * Input: x(int) ����λ��
 * Output: (Employee*) Ա��ָ��
 */
const Employee *List::find(int x) {  //          ����
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
 * Description: ��ӡ����Ա������Ϣ
 * Input: ��
 * Output: ��
 */
void List::print() {  //                   ���
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