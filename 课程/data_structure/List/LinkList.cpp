#include <iostream>
using namespace std;

/* ����ģ���� */
template <typename T> class List {

private:
	typedef T ElemType;

	/* ���Ա�ĵ�����洢�ṹ */
	typedef struct LNode {   // ���嵥����������
		ElemType data;       // ������
		struct LNode *next;  // ָ����(�ṹָ��)
	} LNode, *LinkList;

	LinkList L; // LΪ�������ͷָ�� // �ṹָ�����ͣ�ָ������ĵ�һ�����

public:
	// ���캯��

	List() // Ĭ�Ϲ���һ��������
	{
		L = (LinkList)malloc(sizeof(LNode));  // ����ͷ���
		L->next = nullptr;                    // ��ʼΪ������
	}

	/* ͷ�巨�������������� */
	LinkList List_HeadInsert(int n)
	{
		LNode *s; ElemType temp;
		L = (LinkList)malloc(sizeof(LNode));  // ����ͷ���
		L->next = nullptr;                    // ��ʼΪ������
		for (int i = 0; i < n; i++)
		{
			cin >> temp;

			s = (LNode *)malloc(sizeof(LNode)); // �����½��
			s->data = temp;
			s->next = L->next; // ���½��������
			L->next = s;       // ÿ�ν�s��ָ��������ǰ��
		}
		return L; // ����ͷָ��
	}

	/* β�巨�������������� */
	LinkList List_TailInsert(int n)
	{
		ElemType temp;
		L = (LinkList)malloc(sizeof(LNode)); // ����ͷ���
		LNode *s, *r = L;  // rΪ��βָ��(��ʼ��ָ��ͷ���)
		for (int i = 0; i < n; i++)
		{
			cin >> temp;

			s = (LNode *)malloc(sizeof(LNode)); // �����½��
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
		LNode *p = L->next; int j = 0; // jΪ������
		while (p != nullptr) // �ӵ�һ����㿪ʼ�������ݽ��ĸ���
		{
			j++;
			p = p->next;
		}
		return j;
	}

	/* ����Ų��� */
	LNode *GetElem(int x) // LΪ"��ͷ���"�ĵ������ͷָ��
	{
		LNode *p; int j;

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
	LNode *LocateElem(ElemType e)
	{
		LNode *p = L->next;
		while (p != nullptr && (p->data != e)) // �ӵ�1����㿪ʼ���� data��Ϊe �Ľ��
		{
			p = p->next;
		}
		return p; // �ҵ��󷵻ظý���ָ�룬���򷵻�NULL
	}

	/* ����������ڱ�L�е�x��λ��֮ǰ�����µ�����Ԫ��e */
	bool ListInsert(int x, ElemType e)
	{
		LNode *p, *s;
		p = GetElem(x - 1); // ���Ҳ���λ�õ�ǰ�����
		if (!p) // ����λ�ò��Ϸ�
			return false;

		s = (LNode *)malloc(sizeof(LNode)); // �����½��
		s->data = e;
		s->next = p->next; // �����½��
		p->next = s;       // ԭֱ��ǰ��ָ���½��
		return true;
	}

	/* ɾ��������ɾ����L�е�x��λ�õ�Ԫ�أ�����e����ɾ��Ԫ�ص�ֵ */
	bool ListDelete(int x, ElemType &e)
	{
		LNode *p, *q;
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
		LNode *p = L->next; // �ӵ�һ����㿪ʼ���
		while (p != nullptr)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
}; // List