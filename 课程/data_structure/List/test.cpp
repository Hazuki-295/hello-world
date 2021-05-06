#include <iostream>
using namespace std;

typedef char ElemType;
#define MaxSize 50

/* 链表模板类 */
template <typename T> class List {

public:
    typedef T ElemType;

    /* 线性表的单链表存储结构 */
    typedef struct LNode {   // 定义单链表结点类型
        ElemType data;       // 数据域
        struct LNode *next;  // 指针域(结构指针)
    } LNode, *LinkList;

    LinkList L; // L为单链表的头指针 // 结构指针类型，指向链表的第一个结点

public:
    // 构造函数

    List() // 默认构造一个空链表
    {
        L = (LinkList)malloc(sizeof(LNode));  // 创建头结点
        L->next = nullptr;                    // 初始为空链表
    }

    /* 头插法，逆向建立单链表 */
    LinkList List_HeadInsert(int n)
    {
        LNode *s; ElemType temp;
        L = (LinkList)malloc(sizeof(LNode));  // 创建头结点
        L->next = nullptr;                    // 初始为空链表
        for (int i = 0; i < n; i++)
        {
            cin >> temp;

            s = (LNode *)malloc(sizeof(LNode)); // 创建新结点
            s->data = temp;
            s->next = L->next; // 将新结点插入表中
            L->next = s;       // 每次将s所指结点插在最前端
        }
        return L; // 返回头指针
    }

    /* 尾插法，正向建立单链表 */
    LinkList List_TailInsert(int n)
    {
        ElemType temp;
        L = (LinkList)malloc(sizeof(LNode)); // 创建头结点
        LNode *s, *r = L;  // r为表尾指针(初始化指向头结点)
        for (int i = 0; i < n; i++)
        {
            cin >> temp;

            s = (LNode *)malloc(sizeof(LNode)); // 创建新结点
            s->data = temp; // s结构指针有数据域，但其指针域未初始化(若有下一个结点，则会被下一轮循环赋予地址，也就是当前位置的下一条语句)
            r->next = s;    // 当前表尾结点的指针域 r->next 内，存放指向新结点的指针
            r = s;          // r指向新的表尾结点(保持r仍为表尾指针)
        }
        r->next = nullptr; // 尾结点指针置空
        return L;          // 返回头指针
    }

    /* 求单链表表长 */
    int LinkLength()
    {
        LNode *p = L->next; int j = 0; // j为计数器
        while (p != nullptr) // 从第一个结点开始，计数据结点的个数
        {
            j++;
            p = p->next;
        }
        return j;
    }

    /* 按序号查找 */
    LNode *GetElem(int x) // L为"带头结点"的单链表的头指针
    {
        LNode *p; int j;

        p = L->next; j = 1; // 初始化，p指向第一个结点，j为计数器

        if (x == 0)
            return L;       // 若x等于0，则返回头结点
        if (x < 1)
            return nullptr; // 若x无效，则直接返回NULL
        while (p != nullptr && j < x)  // 从第1个结点开始找，直到 p指向第x个元素(j=x) 或 p为空(达到尾结点)
        {
            p = p->next;
            j++;
        }
        return p; // 若找到，则返回第x个结点的指针；若x大于表长，返回NULL
    }

    /* 按值查找 */
    LNode *LocateElem(ElemType e)
    {
        LNode *p = L->next;
        while (p != nullptr && (p->data != e)) // 从第1个结点开始查找 data域为e 的结点
        {
            p = p->next;
        }
        return p; // 找到后返回该结点的指针，否则返回NULL
    }

    /* 插入操作，在表L中第x个位置之前插入新的数据元素e */
    bool ListInsert(int x, ElemType e)
    {
        LNode *p, *s;
        p = GetElem(x - 1); // 查找插入位置的前驱结点
        if (!p) // 插入位置不合法
            return false;

        s = (LNode *)malloc(sizeof(LNode)); // 创建新结点
        s->data = e;
        s->next = p->next; // 处理新结点
        p->next = s;       // 原直接前驱指向新结点
        return true;
    }

    /* 删除操作，删除表L中第x个位置的元素，并用e返回删除元素的值 */
    bool ListDelete(int x, ElemType &e)
    {
        LNode *p, *q;
        p = GetElem(x - 1); // 查找删除位置的前驱结点
        if (!p || p->next == nullptr) // 删除位置不合法 或 GetElem得到尾结点
            return false;

        q = p->next;       // 令q指向被删除结点
        p->next = q->next; // 将*q结点从链中“断开”
        e = q->data;       // 被删除元素的值赋给e
        free(q);           // 释放结点的存储空间
        return true;
    }

    /* 输出操作，顺序输出线性表L的所有元素值 */
    void PrintList()
    {
        LNode *p = L->next; // 从第一个结点开始输出
        while (p != nullptr)
        {
            cout << p->data << ' ';
            p = p->next;
        }
        cout << endl;
    }
}; // List

/* 以列表为基类，派生出栈模板类 */
template <typename T> class Stack : public List<T> { //将列表的首/末端作为栈顶/底

private:
    typedef T ElemType;

public:
    // 构造函数
    Stack() { InitStack(); } //默认

    /* 初始化一个空栈 */
    void InitStack() { List<T>::List(); }

    /* 判栈空 */
    bool StackEmpty() { return List<T>::LinkLength() == 0; }

    /* 进栈，若栈S未满，则将x加入使之成为新的栈顶 */
    bool Push(ElemType x)
    {
        return List<T>::ListInsert(List<T>::LinkLength() + 1, x);
    }

    /* 出栈，若栈S非空，则弹出栈顶元素，并用x返回其值 */
    bool Pop(ElemType &x)
    {
        return List<T>::ListDelete(List<T>::LinkLength(), x);
    }
}; // Stack




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

