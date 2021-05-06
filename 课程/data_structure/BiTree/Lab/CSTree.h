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
CSTree GetTreeNode(ElemType e)
{
    CSTree p;
    p = (CSTree)malloc(sizeof(CSNode));
    if (!p)
        exit(1);

    p->data = e;
    p->firstchild = NULL;
    p->nextsibling = NULL;
    return p;
}

/* 建立树的孩子-兄弟链表 */
bool CreatTree(CSTree &T)
{
    char first = ' ', second = ' ';
    int result = 0;

    Queue<CSTree> Q;
    Q.InitQueue();

    CSTree p, s, r;

    T = NULL;
    for (scanf("%c%c", &first, &second); second != '#'; result = scanf("%c%c", &first, &second))
    {
        p = GetTreeNode(second);
        Q.EnQueue(p);
        if (first == '#') T = p;
        else {
            Q.GetHead(s);
            while (s->data != first) {
                Q.DeQueue(s); Q.GetHead(s);
            }
            if (!(s->firstchild)) {
                s->firstchild = p;
                r = p;
            }
            else {
                r->nextsibling = p;
                r = p;

            }
        }
    }
    return true;
}

/* 求树的深度 */
int TreeDepth(CSTree T)
{
    int h1, h2;
    if (!T)
        return 0;
    else {
        h1 = TreeDepth(T->firstchild);
        h2 = TreeDepth(T->nextsibling);
        return(((h1 + 1) > h2) ? (h1 + 1) : h2);
    }
}

int main()
{
    CSTree T;

    CreatTree(T);

    printf("%d", TreeDepth(T));
    printf("\n");

    return 0;
}