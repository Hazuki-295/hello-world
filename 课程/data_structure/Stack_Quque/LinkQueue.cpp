#include <iostream>
using namespace std;

/* �б�ڵ�ģ���ࣨ�Ե�������ʽʵ�֣� */
template <typename T> struct ListNode {
	// ��Ա
	T data; ListNode *next; // ������ָ����
	// ���캯��
	ListNode() : data(T()), next(nullptr) {}
	ListNode(T x) : data(x), next(nullptr) {}
	ListNode(T x, ListNode *next) : data(x), next(next) {}
};

/* ������ģ���� */
template<typename T> class Queue {
private:
	using ElemType = T;
	using ListNode = ListNode<T>;

	/* ���е���ʽ�洢���� */
	ListNode *front, *rear; // ���еĶ�ͷ�Ͷ�βָ��(front��ʼ��ָ��ͷ���)

public:
	// ���캯��
	Queue() { InitQueue(); } // Ĭ��

	/* ��ʼ��һ���ն��� */
	void InitQueue() {
		front = rear = new ListNode; // ����ͷ���
		front->next = nullptr;       // ��ʼΪ��
	}

	/* �ж��п� */
	bool QueueEmpty() {
		return rear == front; // �ӿ�����
	}

	/* ��ӣ���x���룬ʹ֮��Ϊ�µĶ�β */
	void EnQueue(ElemType x) {
		ListNode *s = new ListNode(x, nullptr); // �����½��
		rear->next = s; // ��ǰ�ı�βָ���½��
		rear = s;       // ���±�βָ��
	}

	/* ���ӣ�������Q�ǿգ�ɾ����ͷԪ�أ�����x���� */
	bool DeQueue(ElemType &x) {
		if (rear == front) { // �ն�
			return false;
		}
		ListNode *p = front->next; // ��pָ���ͷԪ��
		x = p->data;               // ��x������ֵ
		front->next = p->next;     // ������Ԫ�ش����жϿ�
		if (rear == p) {           // ��ԭ������ֻ��һ����㣬ɾ������
			rear = front;          // ������rearָ��ͷ��㣬�Ա��ֿն�����
		}
		delete p;
		return true;
	}

	/* ����ͷԪ�أ������� Q �ǿգ����� x ���ض�ͷԪ�� �� */
	bool GetHead(ElemType &x) {
		if (rear == front) {   // �ն�
			return false;
		}
		ListNode *p = front->next; // ȡ��ͷԪ��
		x = p->data;               // ��x������ֵ
		return true;
	}
}; // LinkQueue

int main() {
	Queue<int> Q;

	cout << "���������Ԫ�ظ�����";
	int num; cin >> num;

	cout << "������" << num << "������Ԫ�أ�";
	int delete1, insert1;
	for (int i = 0; i < num; i++) {
		cin >> insert1;
		Q.EnQueue(insert1);
	}

	/* ȡջ�� */
	int top; Q.GetHead(top);
	cout << "����Ԫ�أ�" << top << endl;

	/* ��ջ���� */
	cout << "����Ԫ�أ�\n";
	while (!Q.QueueEmpty()) {
		Q.DeQueue(delete1);
		cout << delete1 << " ";
	}
	cout << endl;
}
