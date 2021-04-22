typedef int ElemType;

#include <iostream>
using namespace std;

/* 栈的顺序存储类型 */
struct SqStack {

	ElemType *data; // 存放栈中元素
	int top;        // 栈顶指针
	int maxsize;	// 栈的最大元素个数

public:
	/* 初始化 */
	void InitStack(int size)
	{
		maxsize = size; 
		data = new ElemType[maxsize]; // 数据域
		top = -1; // 初始化栈顶指针
	}

	/* 判栈空 */
	bool StackEmpty()
	{
		if (top == -1)  // 栈空
			return true;
		else              // 栈不空
			return false;
	}

	/* 进栈 */
	bool Push(ElemType x)
	{
		if (top == maxsize - 1)  // 栈满，报错
			return false;
		data[++top] = x;       // 指针先加1，再入栈
		return true;
	}

	/* 出栈 */
	bool Pop(ElemType &x)
	{
		if (top == -1)     // 栈空，报错
			return false;
		x = data[top--]; // 先出栈，指针再减1
		return true;
	}

	/* 读栈顶元素 */
	bool GetTop(ElemType &x)
	{
		if (top == -1)     // 栈空，报错
			return false;
		x = data[top];   // x记录栈顶元素
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

/* 队列的顺序存储类型 */
struct SqQueue {

	ElemType *data;  // 存放队列元素
	int front, rear; // 队头指针和队尾指针
	int maxsize;	 // 队列的最大元素个数

public:
	/* 初始化队列，构造一个空队列Q */
	void InitQueue(int size)
	{
		maxsize = size;
		data = new ElemType[maxsize]; // 数据域
		rear = front = 0;			  // 初始化队首、队尾指针
	}

	/* 判队列空，若队列Q为空，返回true，否则返回false */
	bool QueueEmpty()
	{
		if (rear == front) //队空条件
			return true;
		else
			return false;
	}

	/* 入队，若队列Q未满，将x加入，使之成为新的队尾 */
	bool EnQueue(ElemType x)
	{
		if ((rear + 1) % maxsize == front) // 队满则报错
			return false;
		data[rear] = x;
		rear = (rear + 1) % maxsize; // 队尾指针加1取模
		return true;
	}

	/* 出队，若队列Q非空，删除队头元素，并用x返回 */
	bool DeQueue(ElemType &x)
	{
		if (rear == front) // 队空则报错
			return false;
		x = data[front];
		front = (front + 1) % maxsize; // 队头指针加1取模
		return true;
	}

	/* 从队头到队尾，输出循环队列 */
	void print()
	{
		cout << "waiting queue:";
		if (rear == front) // 若队空
		{
			printf("\n");
			return;
		}

		int i = front;		// 队不空
		while (i != rear)	// 注意，队尾指针指向队尾的下一个元素
		{
			printf(" %d", data[i]);
			i = (i + 1) % maxsize;	// i++
		}
		printf("\n");
	}

	bool GetElem(ElemType x)
	{
		if (x<1 || x>(rear - front + maxsize) % maxsize) // 队列元素
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
	int n, m, q; // 栈的大小，队列大小，操作个数
	cin >> n >> m >> q;
	
	SqStack S; SqQueue Q;
	S.InitStack(n); Q.InitQueue(m);

	char op; int x; // op:运算 1~4 x:车牌号 或 位置

	for (int i = 0; i < q; i++)
	{
		cin >> op >> x;
		switch (op)
		{
		case'1'://一辆车牌号为x的汽车希望进入停车场（如果停车场已满进入等待队伍，如果等待队伍也已经满容量，则不进行任何操作） 
			if (S.Push(x) == false) // 入栈
			{
					Q.EnQueue(x); // 若栈满，入队
			}
			S.print(); Q.print();
			break;

		case'2'://停车场中车牌号为x的汽车离开停车场 (栈，按值查找)
			SqStack temp; // 中转栈
			temp.InitStack(n);
			
			int elem; // 暂存数据
			if (S.GetTop(elem))
			{
				while (elem != x) // 查找车牌为x的车
				{
					S.Pop(elem); // 出栈
					temp.Push(elem); // 进栈 
					S.GetTop(elem);
				}
				S.Pop(elem); // 车牌为x的车出栈
				while (!temp.StackEmpty()) //入栈
				{
					temp.Pop(elem);
					S.Push(elem);
				}
				if (!Q.QueueEmpty()) //队非空
				{
					Q.DeQueue(elem); //出队
					S.Push(elem); //入栈
				}
			}
			delete temp.data;

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
	delete S.data; delete Q.data;

	return 0;
}
