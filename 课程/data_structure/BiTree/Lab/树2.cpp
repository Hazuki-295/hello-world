#include <iostream>
using namespace std;

typedef char ElemType;
#define MaxSize 50

/* 顺序队列模板类 */
template<typename T> class Queue {
private:
    typedef T ElemType;
    /* 队列的顺序存储类型 */
    typedef struct {
        ElemType *data;      // 存放队列元素
        int front, rear; // 队头指针和队尾指针
    } SqQueue;               // 顺序队列的类型定义
    int maxsize;	         // 队列的最大元素个数
    SqQueue Q; // 声明一个顺序队列Q(它是一个结构体变量)
public:
    // 构造函数
    Queue() { InitQueue(); } //默认
    /* 初始化一个空队列 */
    void InitQueue()
    {
        Q.rear = Q.front = 0;			  // 初始化队首、队尾指针
        maxsize = MaxSize;
        Q.data = new ElemType[maxsize]; // 数据域
    }
    /* 初始化一个空队列(指定大小) */
    void InitQueue(int size)
    {
        Q.rear = Q.front = 0;			  // 初始化队首、队尾指针
        maxsize = size;
        Q.data = new ElemType[maxsize]; // 数据域
    }
    /* 判队列空 */
    bool QueueEmpty()
    {
        if (Q.rear == Q.front) //队空条件
            return true;
        else
            return false;
    }
    /* 入队，若队列Q未满，将x加入，使之成为新的队尾 */
    bool EnQueue(ElemType x)
    {
        if ((Q.rear + 1) % maxsize == Q.front) // 队满则报错
            return false;
        Q.data[Q.rear] = x;
        Q.rear = (Q.rear + 1) % maxsize; // 队尾指针加1取模
        return true;
    }
    /* 出队，若队列Q非空，删除队头元素，并用x返回 */
    bool DeQueue(ElemType &x)
    {
        if (Q.rear == Q.front) // 队空则报错
            return false;
        x = Q.data[Q.front];
        Q.front = (Q.front + 1) % maxsize; // 队头指针加1取模
        return true;
    }
    /* 读队头 */
    bool GetHead(ElemType &e)
    {
        if (Q.rear == Q.front) // 队空则报错
            return false;
        e = Q.data[Q.front];
        return true;
    }
}; // SqQueue

/* 树的二叉链表储存结构 */
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

/* 建立树的孩子-兄弟链表结点 */
CSNode *GetTreeNode(ElemType e)
{
    CSTree p;
    p = (CSTree)malloc(sizeof(CSNode));
    if (!p)
        exit(1);
    p->data = e;
    p->firstchild = nullptr;
    p->nextsibling = nullptr;
    return p;
}

/* 求树的深度 */
int TreeDepth(CSTree T)
{
    int depth1, depth2;
    if (!T)
        return 0;
    else {
        depth1 = TreeDepth(T->firstchild);
        depth2 = TreeDepth(T->nextsibling);
        return(((depth1 + 1) > depth2) ? (depth1 + 1) : depth2);
    }
}

typedef struct Node {
    char value; // 结点的值
    int degree; // 结点的度
} Node, *pNode;

int main()
{
    int num; cin >> num;

    pNode data = (Node *)malloc(sizeof(Node) * num);
    for (int i = 0; i < num; i++)
    {
        cin >> data[i].value >> data[i].degree;
    }

    Queue<Node> Q; Q.InitQueue();
    Queue<CSTree> Treequeue; Treequeue.InitQueue();

    CSTree T;
    pNode q = data; // 结构指针

    T = GetTreeNode(q->value);
    CSNode *Treenode, *firstchild, *sibling; // 游标
    Q.EnQueue(*q); // 树根入队列
    Treequeue.EnQueue(T);

    while (!Q.QueueEmpty())
    {
        Node temp;
        Q.DeQueue(temp);// 队头出列
        Treequeue.DeQueue(Treenode);

        if (temp.degree != 0) // 第一个孩子
        {
            q++; Q.EnQueue(*q); // 第一个孩子结点入队列
            firstchild = GetTreeNode(q->value);
            Treequeue.EnQueue(firstchild);
            Treenode->firstchild = firstchild; // 第一个孩子
            sibling = firstchild;
        }

        for (int i = 2; i <= temp.degree; i++) // 第一个孩子的兄弟
        {
            q++; Q.EnQueue(*q); // 孩子的兄弟结点入队列
            sibling->nextsibling = GetTreeNode(q->value);
            Treequeue.EnQueue(sibling->nextsibling);
            sibling = sibling->nextsibling;
        }
    }

    int level = TreeDepth(T);
    printf("%d\n", level);

    return 0;
}