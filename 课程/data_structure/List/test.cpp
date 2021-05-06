#include <iostream>
using namespace std;

typedef char ElemType;
#define MaxSize 50

/* ����ģ���� */
template <typename T> class List {

public:
    typedef T ElemType;

    /* ���Ա�ĵ�����洢�ṹ */
    typedef struct LNode {   // ���嵥����������
        ElemType data;       // ������
        struct LNode *next;  // ָ����(�ṹָ��)
    } LNode, *LinkList;

    LinkList L; // LΪ�������ͷָ�� // �ṹָ�����ͣ�ָ������ĵ�һ�����

public:
    // ���캯��

    List() // Ĭ�Ϲ���һ��������
    {
        L = (LinkList)malloc(sizeof(LNode));  // ����ͷ���
        L->next = nullptr;                    // ��ʼΪ������
    }

    /* ͷ�巨�������������� */
    LinkList List_HeadInsert(int n)
    {
        LNode *s; ElemType temp;
        L = (LinkList)malloc(sizeof(LNode));  // ����ͷ���
        L->next = nullptr;                    // ��ʼΪ������
        for (int i = 0; i < n; i++)
        {
            cin >> temp;

            s = (LNode *)malloc(sizeof(LNode)); // �����½��
            s->data = temp;
            s->next = L->next; // ���½��������
            L->next = s;       // ÿ�ν�s��ָ��������ǰ��
        }
        return L; // ����ͷָ��
    }

    /* β�巨�������������� */
    LinkList List_TailInsert(int n)
    {
        ElemType temp;
        L = (LinkList)malloc(sizeof(LNode)); // ����ͷ���
        LNode *s, *r = L;  // rΪ��βָ��(��ʼ��ָ��ͷ���)
        for (int i = 0; i < n; i++)
        {
            cin >> temp;

            s = (LNode *)malloc(sizeof(LNode)); // �����½��
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
        LNode *p = L->next; int j = 0; // jΪ������
        while (p != nullptr) // �ӵ�һ����㿪ʼ�������ݽ��ĸ���
        {
            j++;
            p = p->next;
        }
        return j;
    }

    /* ����Ų��� */
    LNode *GetElem(int x) // LΪ"��ͷ���"�ĵ������ͷָ��
    {
        LNode *p; int j;

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
    LNode *LocateElem(ElemType e)
    {
        LNode *p = L->next;
        while (p != nullptr && (p->data != e)) // �ӵ�1����㿪ʼ���� data��Ϊe �Ľ��
        {
            p = p->next;
        }
        return p; // �ҵ��󷵻ظý���ָ�룬���򷵻�NULL
    }

    /* ����������ڱ�L�е�x��λ��֮ǰ�����µ�����Ԫ��e */
    bool ListInsert(int x, ElemType e)
    {
        LNode *p, *s;
        p = GetElem(x - 1); // ���Ҳ���λ�õ�ǰ�����
        if (!p) // ����λ�ò��Ϸ�
            return false;

        s = (LNode *)malloc(sizeof(LNode)); // �����½��
        s->data = e;
        s->next = p->next; // �����½��
        p->next = s;       // ԭֱ��ǰ��ָ���½��
        return true;
    }

    /* ɾ��������ɾ����L�е�x��λ�õ�Ԫ�أ�����e����ɾ��Ԫ�ص�ֵ */
    bool ListDelete(int x, ElemType &e)
    {
        LNode *p, *q;
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
        LNode *p = L->next; // �ӵ�һ����㿪ʼ���
        while (p != nullptr)
        {
            cout << p->data << ' ';
            p = p->next;
        }
        cout << endl;
    }
}; // List

/* ���б�Ϊ���࣬������ջģ���� */
template <typename T> class Stack : public List<T> { //���б����/ĩ����Ϊջ��/��

private:
    typedef T ElemType;

public:
    // ���캯��
    Stack() { InitStack(); } //Ĭ��

    /* ��ʼ��һ����ջ */
    void InitStack() { List<T>::List(); }

    /* ��ջ�� */
    bool StackEmpty() { return List<T>::LinkLength() == 0; }

    /* ��ջ����ջSδ������x����ʹ֮��Ϊ�µ�ջ�� */
    bool Push(ElemType x)
    {
        return List<T>::ListInsert(List<T>::LinkLength() + 1, x);
    }

    /* ��ջ����ջS�ǿգ��򵯳�ջ��Ԫ�أ�����x������ֵ */
    bool Pop(ElemType &x)
    {
        return List<T>::ListDelete(List<T>::LinkLength(), x);
    }
}; // Stack




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
void Preorder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        visit(T->data);             // ���ʸ����
        Preorder(T->lchild, visit); // ����������
        Preorder(T->rchild, visit); // ����������
    }
}

/* ������������� */
void Inorder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        Inorder(T->lchild, visit); // ����������
        visit(T->data);            // ���ʸ����
        Inorder(T->rchild, visit); // ����������
    }
}

/* ������������� */
void Postorder(BiTree T, void(*visit)(ElemType &e))
{
    if (T) {
        Postorder(T->lchild, visit); // ����������
        Postorder(T->rchild, visit); // ����������
        visit(T->data);              // ���ʸ����
    }
}

/* ˳�����ģ���� */
template<typename T> class Queue {

private:
    typedef T ElemType;

    /* ���е�˳��洢���� */
    typedef struct {
        ElemType *data;      // ��Ŷ���Ԫ��
        int front, rear; // ��ͷָ��Ͷ�βָ��
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

/* �������������(�ǵݹ��㷨) */
void Inorder2(BiTree T, void(*visit)(ElemType &e))
{
    Stack<BiTree> S; S.InitStack(); BiTree p = T; // ��ʼ��ջS; p�Ǳ���ָ��

    while (p || !S.StackEmpty()) // ջ���� �� p���� ʱѭ��
    {
        if (p) // һ·����
        {
            S.Push(p); // ��ǰ�����ջ
            p = p->lchild; // ���Ӳ��գ�һֱ������
        }
        else // ��ջ
        {
            S.Pop(p); visit(p->data); // ջ��Ԫ�س�ջ�����ʳ�ջ���
            p = p->rchild; // ���������ߣ�p��ֵΪ��ǰ�ڵ���Һ���
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
        Q.DeQueue(p); // ��ͷ������
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

    Inorder2(T, PrintElement); cout << '\n';
    LevelOrder(T, PrintElement); cout << '\n';

    delete T;

    return 0;

}

