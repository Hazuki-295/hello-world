typedef int ElemType;

#include <iostream>
using namespace std;

/* ջ��˳��洢���� */
struct SqStack {

	ElemType *data; // ���ջ��Ԫ��
	int top;        // ջ��ָ��
	int maxsize;	// ջ�����Ԫ�ظ���

public:
	/* ��ʼ�� */
	void InitStack(int size)
	{
		maxsize = size; 
		data = new ElemType[maxsize]; // ������
		top = -1; // ��ʼ��ջ��ָ��
	}

	/* ��ջ�� */
	bool StackEmpty()
	{
		if (top == -1)  // ջ��
			return true;
		else              // ջ����
			return false;
	}

	/* ��ջ */
	bool Push(ElemType x)
	{
		if (top == maxsize - 1)  // ջ��������
			return false;
		data[++top] = x;       // ָ���ȼ�1������ջ
		return true;
	}

	/* ��ջ */
	bool Pop(ElemType &x)
	{
		if (top == -1)     // ջ�գ�����
			return false;
		x = data[top--]; // �ȳ�ջ��ָ���ټ�1
		return true;
	}

	/* ��ջ��Ԫ�� */
	bool GetTop(ElemType &x)
	{
		if (top == -1)     // ջ�գ�����
			return false;
		x = data[top];   // x��¼ջ��Ԫ��
		return true;
	}

	void print()
	{
		cout << "parking lot:";
		for (int i = 0; i < top + 1; i++)
		{
			printf(" %d", data[i]);
		}
		printf("\n");
	}

	bool GetElem(ElemType x)
	{
		if (x<1 || x>top + 1)
		{
			cout << -1 << endl;
			return false;
		}
			
		cout << data[x - 1] << endl;
		return true;
	}
};

/* ���е�˳��洢���� */
struct SqQueue {

	ElemType *data;  // ��Ŷ���Ԫ��
	int front, rear; // ��ͷָ��Ͷ�βָ��
	int maxsize;	 // ���е����Ԫ�ظ���

public:
	/* ��ʼ�����У�����һ���ն���Q */
	void InitQueue(int size)
	{
		maxsize = size;
		data = new ElemType[maxsize]; // ������
		rear = front = 0;			  // ��ʼ�����ס���βָ��
	}

	/* �ж��пգ�������QΪ�գ�����true�����򷵻�false */
	bool QueueEmpty()
	{
		if (rear == front) //�ӿ�����
			return true;
		else
			return false;
	}

	/* ��ӣ�������Qδ������x���룬ʹ֮��Ϊ�µĶ�β */
	bool EnQueue(ElemType x)
	{
		if ((rear + 1) % maxsize == front) // �����򱨴�
			return false;
		data[rear] = x;
		rear = (rear + 1) % maxsize; // ��βָ���1ȡģ
		return true;
	}

	/* ���ӣ�������Q�ǿգ�ɾ����ͷԪ�أ�����x���� */
	bool DeQueue(ElemType &x)
	{
		if (rear == front) // �ӿ��򱨴�
			return false;
		x = data[front];
		front = (front + 1) % maxsize; // ��ͷָ���1ȡģ
		return true;
	}

	/* �Ӷ�ͷ����β�����ѭ������ */
	void print()
	{
		cout << "waiting queue:";
		if (rear == front) // ���ӿ�
		{
			printf("\n");
			return;
		}

		int i = front;		// �Ӳ���
		while (i != rear)	// ע�⣬��βָ��ָ���β����һ��Ԫ��
		{
			printf(" %d", data[i]);
			i = (i + 1) % maxsize;	// i++
		}
		printf("\n");
	}

	bool GetElem(ElemType x)
	{
		if (x<1 || x>(rear - front + maxsize) % maxsize) // ����Ԫ��
		{
			cout << -1 << endl;
			return false;
		}

		cout << data[(front + x - 1) % maxsize] << endl;
		return true;
	}

};

int main()
{
	int n, m, q; // ջ�Ĵ�С�����д�С����������
	cin >> n >> m >> q;
	
	SqStack S; SqQueue Q;
	S.InitStack(n); Q.InitQueue(m);

	char op; int x; // op:���� 1~4 x:���ƺ� �� λ��

	for (int i = 0; i < q; i++)
	{
		cin >> op >> x;
		switch (op)
		{
		case'1'://һ�����ƺ�Ϊx������ϣ������ͣ���������ͣ������������ȴ����飬����ȴ�����Ҳ�Ѿ����������򲻽����κβ����� 
			if (S.Push(x) == false) // ��ջ
			{
					Q.EnQueue(x); // ��ջ�������
			}
			S.print(); Q.print();
			break;

		case'2'://ͣ�����г��ƺ�Ϊx�������뿪ͣ���� (ջ����ֵ����)
			SqStack temp; // ��תջ
			temp.InitStack(n);
			
			int elem; // �ݴ�����
			if (S.GetTop(elem))
			{
				while (elem != x) // ���ҳ���Ϊx�ĳ�
				{
					S.Pop(elem); // ��ջ
					temp.Push(elem); // ��ջ 
					S.GetTop(elem);
				}
				S.Pop(elem); // ����Ϊx�ĳ���ջ
				while (!temp.StackEmpty()) //��ջ
				{
					temp.Pop(elem);
					S.Push(elem);
				}
				if (!Q.QueueEmpty()) //�ӷǿ�
				{
					Q.DeQueue(elem); //����
					S.Push(elem); //��ջ
				}
			}

			S.print(); Q.print();
			break;

		case'3':
			S.GetElem(x);
			break;
		case'4':
			Q.GetElem(x);
			break;
		default:
			break;
		}
	}

	return 0;
}