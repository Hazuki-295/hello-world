#include <iostream>

using namespace std;

/* �б�ڵ�ģ���ࣨ�Ե�������ʽʵ�֣� */
template <typename T> struct ListNode {
	// ��Ա
	T data; ListNode *next; // ������ָ����
	// ���캯��
	ListNode() : data(0), next(nullptr) {}
	ListNode(int x) : data(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : data(x), next(next) {}
};

template <typename T> using LinkList = ListNode<T> *; // ������(ͷָ��)

/* ����ģ���� */
template <typename T> class List {

private:
	using ElemType = T;
	using LinkList = LinkList<T>;
	using ListNode = ListNode<T>;

	LinkList L; // LΪ�������ͷָ��(�ṹָ�����ͣ�ָ������ĵ�һ�����)

public:
	// ���캯��
	List() { InitList(); }; // Ĭ�Ϲ���һ��������

	/* ��ʼ��һ�������� */
	void InitList() // Ĭ�Ϲ���һ��������
	{
		L = (LinkList)malloc(sizeof(ListNode));  // ����ͷ���
		L->next = nullptr;                    // ��ʼΪ������
	}

	/* ͷ�巨�������������� */
	LinkList List_HeadInsert(int n)
	{
		ListNode *s; ElemType temp;
		L = (LinkList)malloc(sizeof(ListNode));  // ����ͷ���
		L->next = nullptr;                    // ��ʼΪ������
		for (int i = 0; i < n; i++)
		{
			cin >> temp;

			s = (ListNode *)malloc(sizeof(ListNode)); // �����½��
			s->data = temp;
			s->next = L->next; // ���½��������
			L->next = s;       // ÿ�ν�s��ָ��������ǰ��
		}
		return L; // ����ͷָ��
		return L; // ����ͷָ��
	}

	/* β�巨�������������� */
	LinkList List_TailInsert(int n)
	{
		ElemType temp;
		L = (LinkList)malloc(sizeof(ListNode)); // ����ͷ���
		ListNode *s, *r = L;  // rΪ��βָ��(��ʼ��ָ��ͷ���)
		for (int i = 0; i < n; i++)
		{
			cin >> temp;

			s = (ListNode *)malloc(sizeof(ListNode)); // �����½��
			s->data = temp; // s�ṹָ���������򣬵���ָ����δ��ʼ��(������һ����㣬��ᱻ��һ��ѭ�������ַ��Ҳ���ǵ�ǰλ�õ���һ�����)
			r->next = s;    // ��ǰ��β����ָ���� r->next �ڣ����ָ���½���ָ��
			r = s;          // rָ���µı�β���(����r��Ϊ��βָ��)
		}
		r->next = nullptr; // β���ָ���ÿ�
		return L;          // ����ͷָ��
	}

	/* ������� */
	int LinkLength()
	{
		ListNode *p = L->next; int j = 0; // jΪ������
		while (p != nullptr) // �ӵ�һ����㿪ʼ�������ݽ��ĸ���
		{
			j++;
			p = p->next;
		}
		return j;
	}

	/* ����Ų��� */
	ListNode *GetElem(int x) // LΪ"��ͷ���"�ĵ������ͷָ��
	{
		ListNode *p; int j;

		p = L->next; j = 1; // ��ʼ����pָ���һ����㣬jΪ������

		if (x == 0)
			return L;       // ��x����0���򷵻�ͷ���
		if (x < 1)
			return nullptr; // ��x��Ч����ֱ�ӷ���NULL
		while (p != nullptr && j < x)  // �ӵ�1����㿪ʼ�ң�ֱ�� pָ���x��Ԫ��(j=x) �� pΪ��(�ﵽβ���)
		{
			p = p->next;
			j++;
		}
		return p; // ���ҵ����򷵻ص�x������ָ�룻��x���ڱ�������NULL
	}

	/* ��ֵ���� */
	ListNode *LocateElem(ElemType e)
	{
		ListNode *p = L->next;
		while (p != nullptr && (p->data != e)) // �ӵ�1����㿪ʼ���� data��Ϊe �Ľ��
		{
			p = p->next;
		}
		return p; // �ҵ��󷵻ظý���ָ�룬���򷵻�NULL
	}

	/* ����������ڱ�L�е�x��λ��֮ǰ�����µ�����Ԫ��e */
	bool ListInsert(int x, ElemType e)
	{
		ListNode *p, *s;
		p = GetElem(x - 1); // ���Ҳ���λ�õ�ǰ�����
		if (!p) // ����λ�ò��Ϸ�
			return false;

		s = (ListNode *)malloc(sizeof(ListNode)); // �����½��
		s->data = e;
		s->next = p->next; // �����½��
		p->next = s;       // ԭֱ��ǰ��ָ���½��
		return true;
	}

	/* ɾ��������ɾ����L�е�x��λ�õ�Ԫ�أ�����e����ɾ��Ԫ�ص�ֵ */
	bool ListDelete(int x, ElemType &e)
	{
		ListNode *p, *q;
		p = GetElem(x - 1); // ����ɾ��λ�õ�ǰ�����
		if (!p || p->next == nullptr) // ɾ��λ�ò��Ϸ� �� GetElem�õ�β���
			return false;

		q = p->next;       // ��qָ��ɾ�����
		p->next = q->next; // ��*q�������С��Ͽ���
		e = q->data;       // ��ɾ��Ԫ�ص�ֵ����e
		free(q);           // �ͷŽ��Ĵ洢�ռ�
		return true;
	}

	/* ���������˳��������Ա�L������Ԫ��ֵ */
	void PrintList()
	{
		ListNode *p = L->next; // �ӵ�һ����㿪ʼ���
		while (p != nullptr)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
}; // List
