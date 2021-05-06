#include <iostream>
using namespace std;

/* ˳���б�ģ���� */
template <typename T> class List {

private:
    typedef T ElemType;

    /* ���Ա��˳��洢�ṹ(��̬����) */
#define InitSize 100     // ���ȵĳ�ʼ������
#define LISTINCREMENT 10 // ��������

    typedef struct {
        ElemType *data;      // �洢�ռ��ַ
        int MaxSize, length; // �������������͵�ǰԪ�ظ���(����)

    } SqList; // ˳�������Ͷ���(��̬����)

    SqList L; // ����һ��˳���L(����һ���ṹ�����)

public:
    // ���캯��
    List() { InitList(); } //Ĭ��

    /* ��ʼ��һ���յ�˳���(Ϊ˳������洢�ռ�) */
    bool InitList()
    {
        L.data = (ElemType *)malloc(InitSize * sizeof(ElemType)); // ����洢�ռ�
        if (!L.data) // �洢����ʧ��
            exit(OVERFLOW);

        L.length = 0;         // �ձ���Ϊ0
        L.MaxSize = InitSize; // ��ʼ�洢����
        return true;
    }

    /* ����������ڱ�L�е�x��λ��֮ǰ�����µ�����Ԫ��e */
    bool ListInsert(int x, ElemType e)
    {
        if (x<1 || x>L.length + 1) // �����λ�÷Ƿ�
            return false;

        ElemType *newbase, *p, *q; // newbase����µĻ���ַ��p��qΪ����ָ�� 
        if (L.length == L.MaxSize) //��ǰ�洢�ռ����������ӷ���
        {
            newbase = (ElemType *)realloc(L.data, (L.MaxSize + LISTINCREMENT) * sizeof(ElemType));
            if (!newbase)
                exit(OVERFLOW);         // �洢����ʧ��
            L.data = newbase;           // �»�ַ
            L.MaxSize += LISTINCREMENT; // ���Ӵ洢����
        }
        q = &(L.data[x - 1]); // qΪ����λ��
        for (p = &(L.data[L.length - 1]); p >= q; p--) // ����λ�ü�֮���Ԫ������
        {
            *(p + 1) = *p;
        }
        *q = e;     // �ڲ���λ�� q �����µ�Ԫ��e
        L.length++; // ����1
        return true;
    }

    /* ɾ��������ɾ����L�е�x��λ�õ�Ԫ�أ�����e����ɾ��Ԫ�ص�ֵ */
    bool ListDelete(int x, ElemType &e)
    {
        if (x<1 || x>L.length) // ɾ����λ�÷Ƿ�
            return false;

        ElemType *p, *q; // p��qΪ����ָ�� 

        p = &(L.data[x - 1]);        // pΪ��ɾ��Ԫ�ص�λ��
        e = *p;                      // ��ɾ��Ԫ�ص�ֵ����e
        q = &(L.data[L.length - 1]); // ��βԪ�ص�λ��
        for (p++; p <= q; p++)       // ��ɾ��Ԫ��֮���Ԫ������
        {
            *(p - 1) = *p;
        }
        L.length--; // ����1
        return true;
    }

    /* ��ֵ���Ҳ������ڱ�L�в��Ҿ��и����ؼ���(e)ֵ��Ԫ�� */
    int LocateElem(ElemType e)
    {
        for (int i = 0; i < L.length; i++)
            if (L.data[i] == e)
                return i + 1; // �±�Ϊi��Ԫ��ֵ����e��������λ��i+1
        return 0;             // �˳�ѭ����˵������ʧ��(0��ʾδ�ҵ�)
    }

    /* ��λ���Ҳ������ҵ���L�е�i��λ�õ�Ԫ�أ�����e������ֵ */
    bool GetElem(int x, ElemType &e)
    {
        if (x<1 || x>L.length)
            return false;
        e = L.data[x - 1]; // λ��Ϊi��Ԫ�أ����±�Ϊi-1
        return true;
    }

    /* ���������˳��������Ա�L������Ԫ��ֵ */
    bool PrintList()
    {
        for (int i = 0; i < L.length; i++)
        {
            cout << L.data[i] << ' ';
        }
        cout << endl;
        return true;
    }

}; // SqList