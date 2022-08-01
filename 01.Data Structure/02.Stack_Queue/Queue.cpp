#include <iostream>
#include "SqQueue.h"
#include "LinkQueue.h"

using namespace std;

ostream &operator<<(ostream &os, SqQueue const &Q) {
    if (QueueEmpty(Q)) return os << "front < ] rear";
    os << "front < ";
    for (int i = Q.front; i != Q.rear; i = (i + 1) % Q.MaxSize) {
        if ((i + 1) % Q.MaxSize != Q.rear) {
            os << Q.data[i] << ", ";
        } else {
            os << Q.data[i] << " ] rear";
        }
    }
    return os;
}

ostream &operator<<(ostream &os, LinkQueue const &Q) {
    if (QueueEmpty(Q)) return os << "front -> [ ] <- rear";
    os << "front -> [ ";
    ListNode *p;
    for (p = Q.front->next; p->next != nullptr; p = p->next) {
        os << p->data << " -> ";
    }
    os << p->data << " ] <- rear";
    return os;
}

int QueueLength(SqQueue Q) {
    return (Q.rear + Q.MaxSize - Q.front) % Q.MaxSize;
}

int QueueLength(LinkQueue Q) {
    return ListLength(Q.front); // 单链表表长
}

template<typename Queue> void testQueue() {
    // SqQueue myQueue;
    Queue myQueue;
    InitQueue(myQueue);

    /* 初始化队列 */
    printf("初始化队列：\n");
    printf("[1] 请输入队列中初始元素的个数：");
    int length;
    cin >> length;
    printf("[2] 请输入%d个初始元素：", length);
    ElemType temp;
    for (int i = 0; i < length; i++) {
        cin >> temp;
        Enqueue(myQueue, temp);
    }
    printf("[3] 队列初始化完成。当前队列中元素个数为：%d，队列中的元素为：", QueueLength(myQueue));
    cout << myQueue << '\n' << endl;

    /* 队列操作测试 */
    enum operationType {
        _Enqueue, _Dequeue, _Front
    };
    printf("队列操作测试：\n");
    int caseCount = 0, opType;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn << "请输入将要执行的操作（01.入队 02.出队 03.队首）：";
        if (!(cin >> opType)) {
            cout << '\n' << endl;
            break;
        }
        switch (--opType) {
            case _Enqueue: {
                cout << prefixWhitespace << "入队操作。\n";
                cout << prefixWhitespace << "请输入入队的元素：";
                cin >> temp;

                cout << prefixOut;
                Enqueue(myQueue, temp);
                printf("入队操作完成。\n");
                break;
            }
            case _Dequeue: {
                cout << prefixWhitespace << "出队操作。\n";

                cout << prefixOut;
                if (!QueueEmpty(myQueue)) {
                    temp = Dequeue(myQueue);
                    printf("出队操作完成，出队的队首元素为：");
                    cout << temp << endl;
                } else {
                    printf("出队操作失败，当前队列为空。\n");
                }
                break;
            }
            case _Front: {
                cout << prefixWhitespace << "队首操作。\n";

                cout << prefixOut;
                if (!QueueEmpty(myQueue)) {
                    temp = GetHead(myQueue);
                    printf("队首操作完成，当前队首元素为：");
                    cout << temp << endl;
                } else {
                    printf("队首操作失败，当前队列为空。\n");
                }
                break;
            }
            default: {
                cout << prefixOut << "输入的操作数错误。" << endl;
            }
        }

        /* 当次操作后输出队列 */
        cout << prefixWhitespace;
        printf("当前队列中元素个数为：%d，队列中的元素为：", QueueLength(myQueue));
        cout << myQueue << '\n' << endl;
    }

    /* 测试完成，销毁队列 */
    printf("测试完成，销毁队列。\n");
    DestroyQueue(myQueue);
}

int main() {
    enum QueueType {
        _SqQueue, _LinkQueue
    };

    cout << "队列测试，请选择队列的实现（01.SqQueue 02.LinkQueue）：";
    int opType;
    cin >> opType;
    cout << endl;

    switch (--opType) {
        case _SqQueue:
            testQueue<SqQueue>();
            break;
        case _LinkQueue:
            testQueue<LinkQueue>();
            break;
        default:
            cout << "输入的操作数错误。" << endl;
    }

    return 0;
}