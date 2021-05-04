#pragma once

typedef int ElemType;

#include <iostream>
using namespace std;

/* ������洢�ṹ */
typedef struct Lnode {

	ElemType data; // ������
	struct Lnode *next; // ָ����(�ṹָ��)

} Lnode, *LinkList;

/* ͷ�巨�������������� */
LinkList List_HeadInsert(LinkList &L, int n) 
{
	LinkList s; ElemType temp;
	L = (LinkList)malloc(sizeof(Lnode)); // ����ͷ���
	L->next = nullptr;                   // ��ʼΪ������
	for (int i = 0; i < n; i++)
	{
		cin >> temp;

		s = (LinkList)malloc(sizeof(Lnode)); // �����½��
		s->data = temp;
		s->next = L->next;
		L->next = s; // ÿ�ν�s��ָ��������ǰ��
	}
	return L; // ����ͷָ��
}

/* β�巨�������������� */
LinkList List_TailInsert(LinkList &L, int n)
{
	ElemType temp;
	L = (LinkList)malloc(sizeof(Lnode)); // ����ͷ���
	LinkList s, r = L;  // rΪ��βָ��(��ʼ��ָ��ͷ���)
	for (int i = 0; i < n; i++)
	{
		cin >> temp;

		s = (LinkList)malloc(sizeof(Lnode));
		s->data = temp;					 // s�ṹָ���������򣬵���ָ����δ��ʼ��(������һ����㣬��ᱻ��һ��ѭ�������ַ��Ҳ���ǵ�ǰλ�õ���һ�����)
		r->next = s;					 // r->next��"��ǰ��β���"��ָ�����ڣ����ָ���½���ָ��
		r = s;							 // rָ���µı�β���(����r��Ϊ��βָ��)

		/* ʵ���ϣ�r��s��ֻ���м��������Ϣ�����Ǳ�������ʵ�Ľ��(��ָ���޹�)�еġ� */
		/* �½ڵ㣬�Ƿ����ڴ浱�еģ��������ֻ��һ�ݶ������������Ū100��ָ���������ָ�������ַ�� */
		/* ��Ҫ���Ĺ������ǹ���Щ���������Σ������ýڵ��ϵ��Ǹ�nextָ�룬ָ����һ���ڴ��(�µĽ��)�� */
	}
	r->next = nullptr;					 // β���ָ���ÿ�
	return L;
}

int LinkLength(LinkList L)
{
	LinkList p = L->next; int j = 0; // jΪ������
	while (p != nullptr)             // �ӵ�һ����㿪ʼ���������ݽ��ĸ���
	{
		j++;
		p = p->next;
	}
	return j;
}

/* ����Ų��ҽ�� */
LinkList GetElem(LinkList L, int x)
{	//LΪ"��ͷ���"�ĵ������ͷָ��
	LinkList p; int j;

	p = L->next; j = 1; //��ʼ����pָ���һ����㣬jΪ������

	if (x == 0)
		return L; //��x����0���򷵻�ͷ���
	if (x < 1)
		return nullptr; //��x��Ч���򷵻�NULL
	while (p != nullptr && j < x)  //�ӵ�1����㿪ʼ�ң�ֱ��pָ���x��Ԫ�� �� pΪ��(�ﵽβ���)
	{
		p = p->next;
		j++;
	}
	return p; //���ҵ����򷵻ص�x������ָ�룻��x���ڱ�������NULL
}

/* ��ֵ���ұ��� */
LinkList LocateElem(LinkList L, int e)
{
	LinkList p = L->next;
	while (p != nullptr && (p->data != e)) //�ӵ�1����㿪ʼ����data��Ϊe�Ľ��
	{
		p = p->next;
	}
	return p; //�ҵ��󷵻ظý���ָ�룬���򷵻�NULL
}

bool ListInsert(LinkList L, int x, ElemType e)
{	//��"��ͷ���"�ĵ�����L�У���x��λ��֮ǰ����Ԫ��e
	LinkList p, s;
	p = GetElem(L, x - 1); //���Ҳ���λ�õ�ǰ�����
	if (!p)
	{
		return false;
	}
	s = (LinkList)malloc(sizeof(Lnode)); //����һ���½��
	s->data = e; 
	s->next = p->next; //�����½��
	p->next = s; //ԭֱ��ǰ��ָ���½��
	return true;
}

bool ListDelete(LinkList L, int x)
{	//��"��ͷ���"�ĵ�����L�У�ɾ����x��Ԫ��
	LinkList p, q;
	p = GetElem(L, x - 1); //����ɾ��λ�õ�ǰ�����
	if (!p)
	{
		return false;
	}
	q = p->next;		   //��qָ��ɾ�����
	p->next = q->next;	   //��*q�������С��Ͽ���
	free(q);			   //�ͷŽ��Ĵ洢�ռ�
	return true;
}

bool PrintList(LinkList L)
{
	LinkList p = L->next; //�ӵ�һ����㿪ʼ���
	while (p != nullptr)
	{
		cout << p->data << endl;
		p = p->next;
	}
	cout << endl;
	return true;
}