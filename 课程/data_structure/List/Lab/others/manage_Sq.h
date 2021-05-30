#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

#include <iostream>
using namespace std;

typedef struct node {
    char name[51];
    char position[51];
    int id;
} node;

/* 顺序表存储结构 */
typedef struct {
    node *elem; //存储空间基址
    int length; //当前长度
    int listsize; //当前分配的存储容量（以sizeof(node)为单位）
} SqList;

SqList InitList()
{
    SqList L;
    L.elem = (node *)malloc(LIST_INIT_SIZE * sizeof(node));//数据域
    if (!L.elem) //存储分配失败
    {
        exit(1);
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return L;
}

bool ListInsert(SqList &L, int x, node e)
{
    if (x<1 || x>L.length + 1) //插入的位置非法(线性表末尾后一个位置属于合法位置)
    {
        cout << -1 << endl;
        return false;
    }
    node *newbase, *p, *q;
    if (L.length == L.listsize)
    {
        newbase = (node *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(node));
        if (!newbase)
        {
            exit(1);
        }
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    q = &(L.elem[x - 1]); //q为插入位置
    for (p = &(L.elem[L.length - 1]); p >= q; p--) //插入位置及之后的元素右移
    {
        *(p + 1) = *p;
    }
    *q = e; //在插入的位置q插入新的e
    L.length++;
    return true;
}

bool ListDelete(SqList &L, int x)
{
    node *p, *q;
    if (x<1 || x>L.length)
    {
        cout << -1 << endl;
        return false;
    }
    p = &(L.elem[x - 1]); //p为被删除元素的位置
    q = &(L.elem[L.length - 1]); //表尾元素的位置
    for (++p; p <= q; p++) //被删除元素之后的元素左移
    {
        *(p - 1) = *p;
    }
    L.length--;
    return true;
}

bool GetElem(SqList &L, int x)
{
    if (x<1 || x>L.length)
    {
        cout << -1 << endl;
        return false;
    }
    cout << L.elem[x - 1].name << ' ' << L.elem[x - 1].position << ' ' << L.elem[x - 1].id << endl;
    return true;
}

bool PrintList(SqList L)
{
    for (int i = 1; i <= L.length; i++)
    {
        cout << L.elem[i - 1].name << ' ' << L.elem[i - 1].position << ' ' << L.elem[i - 1].id << ' ';
    }
    cout << endl;
    return true;
}

int main()
{
    int n, m;//初始n名员工，现在该公司还有m次操作
    cin >> n >> m;

    SqList Staff = InitList();

    for (int i = 1; i <= n; i++)
    {
        node temp;
        cin >> temp.name >> temp.position >> temp.id;
        ListInsert(Staff, i, temp);
    }

    char op;
    int x;

    for (int i = 0; i < m; i++)
    {
        cin >> op >> x;
        switch (op)
        {
        case'1':
            if (ListDelete(Staff, x))//线性表中在位置x的员工离职
                PrintList(Staff);
            break;

        case'2':
            node temp;
            cin >> temp.name >> temp.position >> temp.id;
            if (ListInsert(Staff, x, temp))//有员工入职，需要将员工置入线性表中的位置x处
                PrintList(Staff);
            break;

        case'3':
            GetElem(Staff, x);//查询位置x处员工的信息
            break;

            /* 操作不合法 */
        default:
            cout << -1 << endl;
            break;
        }
    }

    return 0;
}
