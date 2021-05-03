#include <iostream>
using namespace std;

#define MaxSize 50

/* ջ��˳��洢���� */
template<typename T> class SqStack {

private:
    typedef T ElemType;

    ElemType *data; // ���ջ��Ԫ��
    int top;        // ջ��ָ��

    int maxsize;	// ջ�����Ԫ�ظ���

public:
    /* ��ʼ��һ����ջ */
    void InitStack()
    {
        top = -1; // ��ʼ��ջ��ָ��

        maxsize = MaxSize;
        data = new ElemType[maxsize]; // ������
    }

    /* ��ʼ��һ����ջ(ָ����С) */
    void InitStack(int size)
    {
        top = -1; // ��ʼ��ջ��ָ��

        maxsize = size;
        data = new ElemType[maxsize]; // ������
    }

    /* ��ջ�� */
    bool StackEmpty()
    {
        if (top == -1)  // ջ��
            return true;
        else              // ջ����
            return false;
    }

    /* ��ջ����ջSδ������x����ʹ֮��Ϊ�µ�ջ�� */
    bool Push(ElemType x)
    {
        if (top == maxsize - 1)  // ջ��������
            return false;
        data[++top] = x;       // ָ���ȼ�1������ջ
        return true;
    }

    /* ��ջ����ջS�ǿգ��򵯳�ջ��Ԫ�أ�����x������ֵ */
    bool Pop(ElemType &x)
    {
        if (top == -1)     // ջ�գ�����
            return false;
        x = data[top--]; // �ȳ�ջ��ָ���ټ�1
        return true;
    }

    /* ��ջ��Ԫ�� */
    bool GetTop(ElemType &x)
    {
        if (top == -1)     // ջ�գ�����
            return false;
        x = data[top];   // x��¼ջ��Ԫ��
        return true;
    }
}; // SqStack

/* ���е�˳��洢���� */
template<typename T> class SqQueue {

private:
    typedef T ElemType;

    ElemType *data;  // ��Ŷ���Ԫ��
    int front, rear; // ��ͷָ��Ͷ�βָ��

    int maxsize;	 // ���е����Ԫ�ظ���

public:
    /* ��ʼ��һ���ն��� */
    void InitQueue()
    {
        rear = front = 0;			  // ��ʼ�����ס���βָ��

        maxsize = MaxSize;
        data = new ElemType[maxsize]; // ������
    }

    /* ��ʼ��һ���ն���(ָ����С) */
    void InitQueue(int size)
    {
        rear = front = 0;			  // ��ʼ�����ס���βָ��

        maxsize = size;
        data = new ElemType[maxsize]; // ������
    }

    /* �ж��п� */
    bool QueueEmpty()
    {
        if (rear == front) //�ӿ�����
            return true;
        else
            return false;
    }

    /* ��ӣ�������Qδ������x���룬ʹ֮��Ϊ�µĶ�β */
    bool EnQueue(ElemType x)
    {
        if ((rear + 1) % maxsize == front) // �����򱨴�
            return false;
        data[rear] = x;
        rear = (rear + 1) % maxsize; // ��βָ���1ȡģ
        return true;
    }

    /* ���ӣ�������Q�ǿգ�ɾ����ͷԪ�أ�����x���� */
    bool DeQueue(ElemType &x)
    {
        if (rear == front) // �ӿ��򱨴�
            return false;
        x = data[front];
        front = (front + 1) % maxsize; // ��ͷָ���1ȡģ
        return true;
    }
}; // SqQueue