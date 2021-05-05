#include <iostream>
using namespace std;

typedef struct node {
	char name[51];
	char position[51];
	int id;
} node;

/* ������洢�ṹ */
typedef struct Lnode {

	node data; //������
	struct Lnode *next; //ָ����(�ṹָ��)

} Lnode, *LinkList;

/* β�巨�������������� */
LinkList List_TailInsert(LinkList &L, int n)
{
	node temp;
	L = (LinkList)malloc(sizeof(Lnode)); //����ͷ���
	LinkList s, r = L;  //rΪ��βָ��(��ʼ��ָ��ͷ���)
	for (int i = 0; i < n; i++)
	{
		cin >> temp.name >> temp.position >> temp.id;

		s = (LinkList)malloc(sizeof(Lnode));
		s->data = temp;
		r->next = s;
		r = s;							 //rָ���µı�β���(����r��Ϊ��βָ��)
	}
	r->next = nullptr;					 //β���ָ���ÿ�
	return L;
}

int LinkLength(LinkList L)
{
	LinkList p = L->next; int j = 0;
	while (p != nullptr) //�ӵ�һ����㿪ʼ���������ݽ��ĸ���
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

bool ListInsert(LinkList L, int x, node e)
{	//��"��ͷ���"�ĵ�����L�У���x��λ��֮ǰ����Ԫ��e
	LinkList p, s;
	p = GetElem(L, x - 1); //���Ҳ���λ�õ�ǰ�����
	if (!p)
	{
		cout << -1 << endl;
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
		cout << -1 << endl;
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
		cout << p->data.name << ' ' << p->data.position << ' ' << p->data.id << ' ';
		p = p->next;
	}
	cout << endl;
	return true;
}

int main()
{
	int n, m;//��ʼn��Ա�������ڸù�˾����m�β���
	cin >> n >> m;

	LinkList L; //��������ͷָ��

	List_TailInsert(L, n); //��ʼ������

	char op; int x;

	for (int i = 0; i < m; i++)
	{
		cin >> op >> x;
		switch (op)
		{
		case'1':
			if (ListDelete(L, x))//���Ա�����λ��x��Ա����ְ
				PrintList(L);
			break;

		case'2':
			node temp;
			cin >> temp.name >> temp.position >> temp.id;
			if (ListInsert(L, x, temp))//��Ա����ְ����Ҫ��Ա���������Ա��е�λ��x��
				PrintList(L);
			break;

		case'3':
			if (x == 0)
			{
				cout << -1 << endl;
				break;
			}
			LinkList p;
			p = GetElem(L, x);//��ѯλ��x��Ա������Ϣ
			if (!p)
			{
				cout << -1 << endl;
				break;
			}
			cout << p->data.name << ' ' << p->data.position << ' ' << p->data.id << endl;
			break;

			/* �������Ϸ� */
		default:
			cout << -1 << endl;
			break;
		}
	}

	return 0;
}