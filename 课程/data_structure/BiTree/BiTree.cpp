#include <iostream>
using namespace std;

typedef char ElemType;
#define MaxSize 50

/* 二叉树的二叉链表存储表示 */
typedef struct BiTNode {
    ElemType data; // 数据域 
    struct BiTNode *lchild, *rchild; // 左右孩子指针
} BiTNode, *BiTree;

/* 按先序序列建立二叉树的二叉链表 */
bool CreateBiTree(BiTree &T)
{
    char ch; /*cin >> ch;*/
    if ((ch = getchar()) != '\n')
    {
        if (ch == '#')
            T = nullptr;
        else
        {
            if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
            {
                exit(1);
            }
            T->data = ch; // 生成根结点
            CreateBiTree(T->lchild); // 构造左子树
            CreateBiTree(T->rchild); // 构造右子树
        }
    }

    return true;
}

/* 访问结点 */
void PrintElement(ElemType &e)
{
    printf("%c", e);
    return;
}

/* 统计二叉树中叶子结点的个数 */
void CountLeaf(BiTree T, int &count)
{
    if (T)
    {
        if ((!T->lchild) && (!T->rchild)) // 如果是叶子结点
            count++; // 对叶子结点计数
        CountLeaf(T->lchild, count);
        CountLeaf(T->rchild, count);
    }
}

/* 统计二叉树中结点的个数 */
void CountNode(BiTree T, int &count)
{
    if (T)
    {
        //if ((!T->lchild) && (!T->rchild)) // 如果是叶子结点
        count++; // 对叶子结点计数
        CountNode(T->lchild, count);
        CountNode(T->rchild, count);
    }
}

/* 求二叉树的深度 */
int Depth(BiTree T)
{
    int depthval, depthLeft, depthRight;
    if (!T)
        depthval = 0;
    else
    {
        depthLeft = Depth(T->lchild);
        depthRight = Depth(T->rchild);
        depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    return depthval;
}

/* 先序遍历二叉树 */
void Preorder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        visit(T->data);             // 访问根结点
        Preorder(T->lchild, visit); // 遍历左子树
        Preorder(T->rchild, visit); // 遍历右子树
    }
}

/* 中序遍历二叉树 */
void Inorder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        Inorder(T->lchild, visit); // 遍历左子树
        visit(T->data);            // 访问根结点
        Inorder(T->rchild, visit); // 遍历右子树
    }
}

/* 后序遍历二叉树 */
void Postorder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        Postorder(T->lchild, visit); // 遍历左子树
        Postorder(T->rchild, visit); // 遍历右子树
        visit(T->data);              // 访问根结点
    }
}

/* 顺序栈模板类 */
template<typename T> class Stack {

private:
    typedef T ElemType;

    /* 栈的顺序存储类型 */
    typedef struct {
        ElemType *data; // 存放栈中元素
        int top;        // 栈顶指针
    } SqStack;          // 顺序栈的类型定义

    int maxsize;	    // 栈的最大元素个数

    SqStack S; // 声明一个顺序栈S(它是一个结构体变量)

public:
    // 构造函数
    Stack() { InitStack(); } //默认

    /* 初始化一个空栈 */
    void InitStack()
    {
        S.top = -1; // 初始化栈顶指针

        maxsize = MaxSize;
        S.data = new ElemType[maxsize]; // 数据域
    }

    /* 初始化一个空栈(指定大小) */
    void InitStack(int size)
    {
        S.top = -1; // 初始化栈顶指针

        maxsize = size;
        S.data = new ElemType[maxsize]; // 数据域
    }

    /* 判栈空 */
    bool StackEmpty()
    {
        if (S.top == -1)  // 栈空
            return true;
        else              // 栈不空
            return false;
    }

    /* 进栈，若栈S未满，则将x加入使之成为新的栈顶 */
    bool Push(ElemType x)
    {
        if (S.top == maxsize - 1)  // 栈满，报错
            return false;
        S.data[++S.top] = x;       // 指针先加1，再入栈
        return true;
    }

    /* 出栈，若栈S非空，则弹出栈顶元素，并用x返回其值 */
    bool Pop(ElemType &x)
    {
        if (S.top == -1)     // 栈空，报错
            return false;
        x = S.data[S.top--]; // 先出栈，指针再减1
        return true;
    }

    /* 读栈顶元素 */
    bool GetTop(ElemType &x)
    {
        if (S.top == -1)     // 栈空，报错
            return false;
        x = S.data[S.top];   // x记录栈顶元素
        return true;
    }
}; // SqStack

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
}; // SqQueue

/* 中序遍历二叉树(非递归算法) */
void Inorder2(BiTree T, void(*visit)(ElemType &e))
{
    Stack<BiTree> S; S.InitStack(); BiTree p = T; // 初始化栈S; p是遍历指针

    while (p || !S.StackEmpty()) // 栈不空 或 p不空 时循环
    {
        if (p) // 一路向左
        {
            S.Push(p); // 当前结点入栈
            p = p->lchild; // 左孩子不空，一直向左走
        }
        else // 出栈
        {
            S.Pop(p); visit(p->data); // 栈顶元素出栈，访问出栈结点
            p = p->rchild; // 向右子树走，p赋值为当前节点的右孩子
        } // 返回while循环，继续进入if-else语句
    }
}

/* 层次遍历二叉树 */
void LevelOrder(BiTree T, void(*visit)(ElemType &e))
{
    Queue<BiTree> Q; Q.InitQueue(); BiTree p = T; // 初始化辅助队列; p是遍历指针

    Q.EnQueue(T); // 将根结点入队
    while (!Q.QueueEmpty()) // 队列不空则循环
    {
        Q.DeQueue(p); // 队头结点出队
        visit(p->data); // 访问出队结点

        if (p->lchild != NULL)
            Q.EnQueue(p->lchild); // 左子树不空，则左子树根结点入队
        if (p->rchild != NULL)
            Q.EnQueue(p->rchild); // 右子树不空，则右子树根结点入队
    }
}

int main()
{
    BiTree T = new BiTNode; // 创建根结点
    CreateBiTree(T);

    Inorder2(T, PrintElement); cout << '\n';
    LevelOrder(T, PrintElement); cout << '\n';

    delete T;

    return 0;

}