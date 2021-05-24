#include <iostream>
#include <queue>
using namespace std;

#define MaxVertexNum 100  // ͼ�ж�����Ŀ�����ֵ

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

template <typename T> using ArcNode = ListNode<T>; // ��(��)���

template <typename VertexType> struct VNode // ����(��)���
{
	VertexType data;      // ������Ϣ
	ArcNode *first;       // ָ���һ�������ö���Ļ���ָ��
};
template <typename T> using AdjList = VNode<T>[MaxVertexNum]; // �ڽӱ�

/* ͼGraphģ���ࣨ�ڽӱ� */
template <typename VertexType> class Graph { // VertexType���������������

private:
	/* ͼ���ڽӱ�洢�ṹ */
	AdjList vertices;   // �ڽӱ�
	int vexnum, arcnum; // ͼ�Ķ������ͻ���

	bool visited[MaxVertexNum]; // ���ʱ������

	queue<int> Q; // ��������Q

public:
	stringstream ss; // ���ڴ�����

	Graph(int Vexnum, int Edgenum) :vexnum(Vexnum), arcnum(Edgenum)
	{
		/* ��ʼ�� */
		for (int i = 0; i < vexnum; i++) Vex[i] = i + 1; // ������Ϣ��1����

		int x, y; // �ڽӵ���������
		for (int i = 0; i < arcnum; i++) // ����ÿ����
		{
			cin >> x >> y;
			if (Edge[x - 1][y - 1] != 0)
			{
				i--;
				continue;
			}
			else
			{
				Edge[x - 1][y - 1] = 1;
				Edge[y - 1][x - 1] = 1;
			}
		}
	}

	/* ��ͼG�ж���x�ĵ�һ���ڽӵ㣬�����򷵻ض���š���xû���ڽӵ��ͼ�в�����x���򷵻�-1 */
	int FirstNeighbor(int x)
	{
		if (x >= vexnum) return -1; // ͼ�в�����x������-1

		for (int i = 0; i < vexnum; i++)
			if (Edge[x][i] != 0)    // �����ڵ�һ���ڽӵ㣬�򷵻ض����
				return i;

		return -1; // ��xû���ڽӵ㣬����-1
	}

	/* ����ͼG�ж���y�Ƕ���x��һ���ڽӵ㣬�򷵻س�y�ⶥ��x����һ���ڽӵ�Ķ���š���y��x�����һ���ڽӵ㣬�򷵻�-1 */
	int NextNeighbor(int x, int y)
	{
		if (y == vexnum - 1) return -1; // Խ�磬y+1�������vexnum����ѭ������ִ��
		for (int i = y + 1; i < vexnum; i++)
			if (Edge[x][i] != 0) // ��y�ⶥ��x����һ���ڽӵ�
				return i;

		return -1; // ��y��x�����һ���ڽӵ㣬�򷵻�-1
	}

	/* ����ͼ�еĶ���v */
	void visit(int v) { ss << Vex[v] << " "; }

	/* ��ͼG����������ȱ��� */
	void DFSTraverse()
	{
		for (int v = 0; v < vexnum; v++) // ��ʼ�����ʱ������
			visited[v] = false;
		for (int v = 0; v < vexnum; v++) // ���������Ǵ�v=0��ʼ����
			if (!visited[v]) DFS(v);
	}
	void DFSTraverse(int x)
	{
		for (int v = 0; v < vexnum; v++) // ��ʼ�����ʱ������
			visited[v] = false;
		for (int v = x; v < vexnum; v++) // ���������Ǵ�v=x��ʼ����
			if (!visited[v]) DFS(v);
	}
	void DFS(int v) // �Ӷ���v������������ȱ���ͼG
	{
		visit(v); visited[v] = true; // ���ʶ���v
		for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w))
			if (!visited[w]) DFS(w); //wΪv����δ���ʵ��ڽӶ���
	}

	/* ��ͼG���й�����ȱ��� */
	void BFSTraverse()
	{
		for (int i = 0; i < vexnum; i++)  // ��ʼ�����ʱ������
			visited[i] = false;

		Q = queue<int>();                 // ��ʼ����������Q

		for (int i = 0; i < vexnum; i++)  // ��0�Ŷ��㿪ʼ����
			if (!visited[i]) BFS(i);      // ��ÿ����ͨ��������һ��BFS
	}
	void BFSTraverse(int x)
	{
		for (int i = 0; i < vexnum; i++)  // ��ʼ�����ʱ������
			visited[i] = false;

		Q = queue<int>();                 // ��ʼ����������Q

		for (int i = x; i < vexnum; i++)  // ��x�Ŷ��㿪ʼ����
			if (!visited[i]) BFS(i);      // ��ÿ����ͨ��������һ��BFS
	}
	void BFS(int v) // �Ӷ���v������������ȱ���ͼG
	{
		visit(v); visited[v] = true; // ���ʶ���v
		Q.push(v);                   // ����v�����Q

		while (!Q.empty())
		{
			v = Q.front(); Q.pop(); // ����v������
			for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) // ���v�����ڽӵ�
			{
				if (!visited[w]) // wΪv����δ���ʵ��ڽӵ�
				{
					visit(w); visited[w] = true;
					Q.push(w); // ����w�����(��һ�������ʵĶ���)
				}
			}
		}
	}
};
