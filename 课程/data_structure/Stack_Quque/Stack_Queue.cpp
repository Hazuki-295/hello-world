#include <iostream>
using namespace std;

#define MaxSize 50

/* 顺序栈模板类 */
template<typename T> class Stack {

private:
    typedef T ElemType;

    /* 栈的顺序存储类型 */
    typedef struct {
        ElemType *data; // 存放栈中元素
        int top;        // 栈顶指针
    } SqStack;          // 顺序栈的类型定义

    int maxsize;	    // 栈的最大元素个数

    SqStack S; // 声明一个顺序栈S(它是一个结构体变量)

public:
    // 构造函数
    Stack() { InitStack(); } //默认

    /* 初始化一个空栈 */
    void InitStack()
    {
        S.top = -1; // 初始化栈顶指针

        maxsize = MaxSize;
        S.data = new ElemType[maxsize]; // 数据域
    }

    /* 初始化一个空栈(指定大小) */
    void InitStack(int size)
    {
        S.top = -1; // 初始化栈顶指针

        maxsize = size;
        S.data = new ElemType[maxsize]; // 数据域
    }

    /* 判栈空 */
    bool StackEmpty()
    {
        if (S.top == -1)  // 栈空
            return true;
        else              // 栈不空
            return false;
    }

    /* 进栈，若栈S未满，则将x加入使之成为新的栈顶 */
    bool Push(ElemType x)
    {
        if (S.top == maxsize - 1)  // 栈满，报错
            return false;
        S.data[++S.top] = x;       // 指针先加1，再入栈
        return true;
    }

    /* 出栈，若栈S非空，则弹出栈顶元素，并用x返回其值 */
    bool Pop(ElemType &x)
    {
        if (S.top == -1)     // 栈空，报错
            return false;
        x = S.data[S.top--]; // 先出栈，指针再减1
        return true;
    }

    /* 读栈顶元素 */
    bool GetTop(ElemType &x)
    {
        if (S.top == -1)     // 栈空，报错
            return false;
        x = S.data[S.top];   // x记录栈顶元素
        return true;
    }
}; // SqStack

/* 顺序队列模板类 */
template<typename T> class Queue {

private:
    typedef T ElemType;

    /* 队列的顺序存储类型 */
    typedef struct {
        ElemType *data;      // 存放队列元素
        int front, rear; // 队头指针和队尾指针
    } SqQueue;               // 顺序队列的类型定义

    int maxsize;	         // 队列的最大元素个数

    SqQueue Q; // 声明一个顺序队列Q(它是一个结构体变量)

public:
    // 构造函数
    Queue() { InitQueue(); } //默认

    /* 初始化一个空队列 */
    void InitQueue()
    {
        Q.rear = Q.front = 0;			  // 初始化队首、队尾指针

        maxsize = MaxSize;
        Q.data = new ElemType[maxsize]; // 数据域
    }

    /* 初始化一个空队列(指定大小) */
    void InitQueue(int size)
    {
        Q.rear = Q.front = 0;			  // 初始化队首、队尾指针

        maxsize = size;
        Q.data = new ElemType[maxsize]; // 数据域
    }

    /* 判队列空 */
    bool QueueEmpty()
    {
        if (Q.rear == Q.front) //队空条件
            return true;
        else
            return false;
    }

    /* 入队，若队列Q未满，将x加入，使之成为新的队尾 */
    bool EnQueue(ElemType x)
    {
        if ((Q.rear + 1) % maxsize == Q.front) // 队满则报错
            return false;
        Q.data[Q.rear] = x;
        Q.rear = (Q.rear + 1) % maxsize; // 队尾指针加1取模
        return true;
    }

    /* 出队，若队列Q非空，删除队头元素，并用x返回 */
    bool DeQueue(ElemType &x)
    {
        if (Q.rear == Q.front) // 队空则报错
            return false;
        x = Q.data[Q.front];
        Q.front = (Q.front + 1) % maxsize; // 队头指针加1取模
        return true;
    }
}; // SqQueue