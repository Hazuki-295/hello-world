#include <iostream>
using namespace std;

typedef char ElemType;
#define MaxSize 50

/* ˳��ջģ���� */
template<typename T> class Stack {

private:
    typedef T ElemType;

    /* ջ��˳��洢���� */
    typedef struct {
        ElemType *data; // ���ջ��Ԫ��
        int top;        // ջ��ָ��
    } SqStack;          // ˳��ջ�����Ͷ���

    int maxsize;	    // ջ�����Ԫ�ظ���

    SqStack S; // ����һ��˳��ջS(����һ���ṹ�����)

public:
    // ���캯��
    Stack() { InitStack(); } //Ĭ��

    /* ��ʼ��һ����ջ */
    void InitStack()
    {
        S.top = -1; // ��ʼ��ջ��ָ��

        maxsize = MaxSize;
        S.data = new ElemType[maxsize]; // ������
    }

    /* ��ʼ��һ����ջ(ָ����С) */
    void InitStack(int size)
    {
        S.top = -1; // ��ʼ��ջ��ָ��

        maxsize = size;
        S.data = new ElemType[maxsize]; // ������
    }

    /* ��ջ�� */
    bool StackEmpty()
    {
        if (S.top == -1)  // ջ��
            return true;
        else              // ջ����
            return false;
    }

    /* ��ջ����ջSδ������x����ʹ֮��Ϊ�µ�ջ�� */
    bool Push(ElemType x)
    {
        if (S.top == maxsize - 1)  // ջ��������
            return false;
        S.data[++S.top] = x;       // ָ���ȼ�1������ջ
        return true;
    }

    /* ��ջ����ջS�ǿգ��򵯳�ջ��Ԫ�أ�����x������ֵ */
    bool Pop(ElemType &x)
    {
        if (S.top == -1)     // ջ�գ�����
            return false;
        x = S.data[S.top--]; // �ȳ�ջ��ָ���ټ�1
        return true;
    }

    /* ��ջ��Ԫ�� */
    bool GetTop(ElemType &x)
    {
        if (S.top == -1)     // ջ�գ�����
            return false;
        x = S.data[S.top];   // x��¼ջ��Ԫ��
        return true;
    }
}; // SqStack

/* ˳�����ģ���� */
template<typename T> class Queue {

private:
    typedef T ElemType;

    /* ���е�˳��洢���� */
    typedef struct {
        ElemType *data;      // ��Ŷ���Ԫ��
        int front, rear;     // ��ͷָ��Ͷ�βָ��
    } SqQueue;               // ˳����е����Ͷ���

    int maxsize;	         // ���е����Ԫ�ظ���

    SqQueue Q; // ����һ��˳�����Q(����һ���ṹ�����)

public:
    // ���캯��
    Queue() { InitQueue(); } //Ĭ��

    /* ��ʼ��һ���ն��� */
    void InitQueue()
    {
        Q.rear = Q.front = 0;			  // ��ʼ�����ס���βָ��

        maxsize = MaxSize;
        Q.data = new ElemType[maxsize]; // ������
    }

    /* ��ʼ��һ���ն���(ָ����С) */
    void InitQueue(int size)
    {
        Q.rear = Q.front = 0;			  // ��ʼ�����ס���βָ��

        maxsize = size;
        Q.data = new ElemType[maxsize]; // ������
    }

    /* �ж��п� */
    bool QueueEmpty()
    {
        if (Q.rear == Q.front) //�ӿ�����
            return true;
        else
            return false;
    }

    /* ��ӣ�������Qδ������x���룬ʹ֮��Ϊ�µĶ�β */
    bool EnQueue(ElemType x)
    {
        if ((Q.rear + 1) % maxsize == Q.front) // �����򱨴�
            return false;
        Q.data[Q.rear] = x;
        Q.rear = (Q.rear + 1) % maxsize; // ��βָ���1ȡģ
        return true;
    }

    /* ���ӣ�������Q�ǿգ�ɾ����ͷԪ�أ�����x���� */
    bool DeQueue(ElemType &x)
    {
        if (Q.rear == Q.front) // �ӿ��򱨴�
            return false;
        x = Q.data[Q.front];
        Q.front = (Q.front + 1) % maxsize; // ��ͷָ���1ȡģ
        return true;
    }
}; // SqQueue

/* �������Ķ�������洢��ʾ */
typedef struct BiTNode {
    ElemType data; // ������ 
    struct BiTNode *lchild, *rchild; // ���Һ���ָ��
} BiTNode, *BiTree;

/* ���������н����������Ķ������� */
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
            T->data = ch; // ���ɸ����
            CreateBiTree(T->lchild); // ����������
            CreateBiTree(T->rchild); // ����������
        }
    }

    return true;
}

/* ���ʽ�� */
void PrintElement(ElemType &e)
{
    printf("%c", e);
    return;
}

/* ͳ�ƶ�������Ҷ�ӽ��ĸ��� */
void CountLeaf(BiTree T, int &count)
{
    if (T)
    {
        if ((!T->lchild) && (!T->rchild)) // �����Ҷ�ӽ��
            count++; // ��Ҷ�ӽ�����
        CountLeaf(T->lchild, count);
        CountLeaf(T->rchild, count);
    }
}

/* ͳ�ƶ������н��ĸ��� */
void CountNode(BiTree T, int &count)
{
    if (T)
    {
        //if ((!T->lchild) && (!T->rchild)) // �����Ҷ�ӽ��
        count++; // ��Ҷ�ӽ�����
        CountNode(T->lchild, count);
        CountNode(T->rchild, count);
    }
}

/* ������������ */
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

/* ������������� */
void PreOrder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        visit(T->data);             // ���ʸ����
        PreOrder(T->lchild, visit); // ����������
        PreOrder(T->rchild, visit); // ����������
    }
}

/* ������������� */
void InOrder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        InOrder(T->lchild, visit); // ����������
        visit(T->data);            // ���ʸ����
        InOrder(T->rchild, visit); // ����������
    }
}

/* ������������� */
void PostOrder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        PostOrder(T->lchild, visit); // ����������
        PostOrder(T->rchild, visit); // ����������
        visit(T->data);              // ���ʸ����
    }
}


/* �������������(�ǵݹ��㷨) */
void InOrder2(BiTree T, void(*visit)(ElemType &e))
{
    Stack<BiTree> S; S.InitStack(); BiTree p = T; // ��ʼ��ջS; p�Ǳ���ָ��
    while (p || !S.StackEmpty()) // ջ����(���ڴ����ʽ��) �� p����(��������������ǿ���) ʱѭ��
    {
        if (p) // һ·���� (�� ���������գ��������֮)
        {
            S.Push(p);     // ��ǰ�����ջ
            p = p->lchild; // ���Ӳ��գ�һֱ������
        }
        else // ��ջ����ת���ջ����������
        {
            S.Pop(p); visit(p->data); // ջ��Ԫ�س�ջ�����ʳ�ջ���
            p = p->rchild;            // ���������ߣ�p��ֵΪ��ǰ�����Һ���
                                      // ���Һ���Ϊ�գ��ó�ջ��������ϣ��������ջ
        } // ����whileѭ������������if-else���
    }
}

/* �������������(�ǵݹ��㷨) */
void PreOrder2(BiTree T, void(*visit)(ElemType &e))
{
    Stack<BiTree> S; S.InitStack(); BiTree p = T; // ��ʼ��ջS; p�Ǳ���ָ��
    while (p || !S.StackEmpty()) // ջ����(���ڴ����ʽ��) �� p����(��������������ǿ���) ʱѭ��
    {
        if (p) // һ·���� (�� ���������գ��������֮)
        {
            visit(p->data); S.Push(p); // ���ʵ�ǰ��㣬����ջ
            p = p->lchild;             // ���Ӳ��գ�һֱ������
        }
        else // ��ջ����ת���ջ����������
        {
            S.Pop(p);       // ջ��Ԫ�س�ջ
            p = p->rchild;  // ���������ߣ�p��ֵΪ��ǰ�����Һ���
                            // ���Һ���Ϊ�գ��ó�ջ��������ϣ��������ջ
        } // ����whileѭ������������if-else���
    }
}

/* ��α��������� */
void LevelOrder(BiTree T, void(*visit)(ElemType &e))
{
    Queue<BiTree> Q; Q.InitQueue(); BiTree p = T; // ��ʼ����������; p�Ǳ���ָ��

    Q.EnQueue(T); // ����������
    while (!Q.QueueEmpty()) // ���в�����ѭ��
    {
        Q.DeQueue(p);   // ��ͷ������
        visit(p->data); // ���ʳ��ӽ��

        if (p->lchild != NULL)
            Q.EnQueue(p->lchild); // ���������գ�����������������
        if (p->rchild != NULL)
            Q.EnQueue(p->rchild); // ���������գ�����������������
    }
}


int main()
{
    BiTree T = new BiTNode; // ���������
    CreateBiTree(T);

    InOrder2(T, PrintElement); cout << '\n';
    LevelOrder(T, PrintElement); cout << '\n';

    delete T;

    return 0;

}