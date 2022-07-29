#pragma once

typedef int ElemType;

/* 队列的顺序表示（以循环队列形式实现） */
#define InitSize 10
typedef struct {
    ElemType *data; // 队列中的元素，动态分配
    int MaxSize;    // 队列的最大容量
    int front;      // 队头指针，指向队头元素
    int rear;       // 队尾指针，指向队尾元素的下一个位置（下一个入队元素的插入位置）
} SqQueue;          // 循环队列的类型定义

/* 初始化队列。构造一个空队列。 */
void InitQueue(SqQueue &Q) {
    Q.data = new ElemType[Q.MaxSize = InitSize];
    Q.front = Q.rear = 0; // 初始化队首、队尾指针
}

/* 销毁操作。销毁队列，并释放队列Q所占用的内存空间。 */
void DestroyQueue(SqQueue &Q) {
    delete[] Q.data;
}

/* 判空操作。若Q为空队列，则返回true，否则返回false。 */
bool QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear; // 队空条件
}

/* 入队：若队列Q未满，则将e插至队尾指针所指的位置，成为新的队尾。 */
void Enqueue(SqQueue &Q, ElemType e) {
    if ((Q.rear + 1) % Q.MaxSize == Q.front) { // 当前存储空间已满，扩容
        ElemType *p = Q.data;
        Q.data = new ElemType[Q.MaxSize << 1]; // 容量加倍
        for (int i = 0; i < Q.MaxSize; i++) {  // 将数据复制到新区域
            Q.data[i] = p[i];
        }
        delete[] p;
        Q.MaxSize <<= 1; // 更新最大容量
    }
    Q.data[Q.rear] = e;                // 插入队尾元素
    Q.rear = (Q.rear + 1) % Q.MaxSize; // 更新队尾指针
}

/* 出队：若队列Q非空，删除队头元素，并返回其值。 */
ElemType Dequeue(SqQueue &Q) {
    ElemType e = Q.data[Q.front];        // 队头元素
    Q.front = (Q.front + 1) % Q.MaxSize; // 更新队头指针
    return e;
}

/* 读队头元素：若队列Q非空，则返回队头元素的引用。 */
ElemType &GetHead(SqQueue Q) {
    return Q.data[Q.front]; // 返回队头元素的引用
}