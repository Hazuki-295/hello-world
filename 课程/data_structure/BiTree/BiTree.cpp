#include <iostream>
using namespace std;

typedef char ElemType;

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

/* 先序遍历的递归算法 */
void Preorder(BiTree T, void(*visit)(ElemType &e)) // 先序遍历二叉树 
{
    if (T) {
        visit(T->data);             // 访问根结点
        Preorder(T->lchild, visit); // 遍历左子树
        Preorder(T->rchild, visit); // 遍历右子树
    }
}

void Inorder(BiTree T, void(*visit)(ElemType &e)) // 中序遍历二叉树 
{
    if (T) {
        Inorder(T->lchild, visit); // 遍历左子树
        visit(T->data);            // 访问根结点
        Inorder(T->rchild, visit); // 遍历右子树
    }
}

void Postorder(BiTree T, void(*visit)(ElemType &e)) // 后序遍历二叉树 
{
    if (T) {
        Postorder(T->lchild, visit); // 遍历左子树
        Postorder(T->rchild, visit); // 遍历右子树
        visit(T->data);              // 访问根结点
    }
}

int main() 
{
    int count = 0, depth;
    BiTree T = (BiTNode *)malloc(sizeof(BiTNode)); // 创建根结点
    CreateBiTree(T);

    Preorder(T, PrintElement); cout << '\n';
    Inorder(T, PrintElement); cout << '\n';
    Postorder(T, PrintElement); cout << '\n';

    CountNode(T, count);
    depth = Depth(T);

    cout << count << '\n' << depth << '\n';

    return 0;

}


