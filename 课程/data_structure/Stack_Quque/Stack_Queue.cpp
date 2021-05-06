#include <iostream>
using namespace std;

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