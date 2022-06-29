#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

#include <iostream>
using namespace std;

typedef struct node {
    char name[51];
    char position[51];
    int id;
} node;

/* ˳���洢�ṹ */
typedef struct {
    node *elem; //�洢�ռ��ַ
    int length; //��ǰ����
    int listsize; //��ǰ����Ĵ洢��������sizeof(node)Ϊ��λ��
} SqList;

SqList InitList()
{
    SqList L;
    L.elem = (node *)malloc(LIST_INIT_SIZE * sizeof(node));//������
    if (!L.elem) //�洢����ʧ��
    {
        exit(1);
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return L;
}

bool ListInsert(SqList &L, int x, node e)
{
    if (x<1 || x>L.length + 1) //�����λ�÷Ƿ�(���Ա�ĩβ��һ��λ�����ںϷ�λ��)
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
    q = &(L.elem[x - 1]); //qΪ����λ��
    for (p = &(L.elem[L.length - 1]); p >= q; p--) //����λ�ü�֮���Ԫ������
    {
        *(p + 1) = *p;
    }
    *q = e; //�ڲ����λ��q�����µ�e
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
    p = &(L.elem[x - 1]); //pΪ��ɾ��Ԫ�ص�λ��
    q = &(L.elem[L.length - 1]); //��βԪ�ص�λ��
    for (++p; p <= q; p++) //��ɾ��Ԫ��֮���Ԫ������
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
    int n, m;//��ʼn��Ա�������ڸù�˾����m�β���
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
            if (ListDelete(Staff, x))//���Ա�����λ��x��Ա����ְ
                PrintList(Staff);
            break;

        case'2':
            node temp;
            cin >> temp.name >> temp.position >> temp.id;
            if (ListInsert(Staff, x, temp))//��Ա����ְ����Ҫ��Ա���������Ա��е�λ��x��
                PrintList(Staff);
            break;

        case'3':
            GetElem(Staff, x);//��ѯλ��x��Ա������Ϣ
            break;

            /* �������Ϸ� */
        default:
            cout << -1 << endl;
            break;
        }
    }

    return 0;
}
