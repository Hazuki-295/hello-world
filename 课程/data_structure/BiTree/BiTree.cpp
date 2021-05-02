#include <iostream>
using namespace std;

typedef char ElemType;

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

/* ��������ĵݹ��㷨 */
void Preorder(BiTree T, void(*visit)(ElemType &e)) // ������������� 
{
    if (T) {
        visit(T->data);             // ���ʸ����
        Preorder(T->lchild, visit); // ����������
        Preorder(T->rchild, visit); // ����������
    }
}

void Inorder(BiTree T, void(*visit)(ElemType &e)) // ������������� 
{
    if (T) {
        Inorder(T->lchild, visit); // ����������
        visit(T->data);            // ���ʸ����
        Inorder(T->rchild, visit); // ����������
    }
}

void Postorder(BiTree T, void(*visit)(ElemType &e)) // ������������� 
{
    if (T) {
        Postorder(T->lchild, visit); // ����������
        Postorder(T->rchild, visit); // ����������
        visit(T->data);              // ���ʸ����
    }
}

int main() 
{
    int count = 0, depth;
    BiTree T = (BiTNode *)malloc(sizeof(BiTNode)); // ���������
    CreateBiTree(T);

    Preorder(T, PrintElement); cout << '\n';
    Inorder(T, PrintElement); cout << '\n';
    Postorder(T, PrintElement); cout << '\n';

    CountNode(T, count);
    depth = Depth(T);

    cout << count << '\n' << depth << '\n';

    return 0;

}


