#include <iostream>
using namespace std;

typedef char ElemType;
#define MaxSize 50

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
    /* ����ͷ */
    bool GetHead(ElemType &e)
    {
        if (Q.rear == Q.front) // �ӿ��򱨴�
            return false;
        e = Q.data[Q.front];
        return true;
    }
}; // SqQueue

/* ���Ķ���������ṹ */
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

/* �������ĺ���-�ֵ������� */
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

/* ��������� */
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
    char value; // ����ֵ
    int degree; // ���Ķ�
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
    pNode q = data; // �ṹָ��

    T = GetTreeNode(q->value);
    CSNode *Treenode, *firstchild, *sibling; // �α�
    Q.EnQueue(*q); // ���������
    Treequeue.EnQueue(T);

    while (!Q.QueueEmpty())
    {
        Node temp;
        Q.DeQueue(temp);// ��ͷ����
        Treequeue.DeQueue(Treenode);

        if (temp.degree != 0) // ��һ������
        {
            q++; Q.EnQueue(*q); // ��һ�����ӽ�������
            firstchild = GetTreeNode(q->value);
            Treequeue.EnQueue(firstchild);
            Treenode->firstchild = firstchild; // ��һ������
            sibling = firstchild;
        }

        for (int i = 2; i <= temp.degree; i++) // ��һ�����ӵ��ֵ�
        {
            q++; Q.EnQueue(*q); // ���ӵ��ֵܽ�������
            sibling->nextsibling = GetTreeNode(q->value);
            Treequeue.EnQueue(sibling->nextsibling);
            sibling = sibling->nextsibling;
        }
    }

    int level = TreeDepth(T);
    printf("%d\n", level);

    return 0;
}