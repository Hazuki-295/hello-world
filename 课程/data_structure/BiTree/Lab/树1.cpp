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

/* �������ĺ���-�ֵ����� */
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

/* ��������� */
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