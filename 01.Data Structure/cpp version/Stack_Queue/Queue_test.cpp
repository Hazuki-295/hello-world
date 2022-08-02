#include <iostream>
#include "Queue.h"

using namespace std;

struct Customer {      // 顾客类
    int window;        // 所属窗口（队列）
    unsigned int time; // 服务时长
};

ostream &operator<<(ostream &os, Customer const &C) {
    return os << C.time;
}

void printWindows(Queue<Customer> windows[], int numOfWin, int servTime) {
    cout << "银行服务模拟，当前剩余服务时间：" << servTime << endl;
    for (int i = 0; i < numOfWin; i++) {
        cout << "- Windows[" + to_string(i) + "]: " << windows[i] << '\n';
    }
    cout << endl;
}

int bestWindow(Queue<Customer> windows[], int numOfWin) { // 为新到顾客确定最佳队列
    int minSize = windows[0].size(), optimalWin = 0; // 最优队列（窗口）
    for (int i = 1; i < numOfWin; i++) {   // 在所有窗口中
        if (windows[i].size() < minSize) { // 挑选出队列最短者
            minSize = windows[i].size();
            optimalWin = i;
        }
    }
    return optimalWin; // 返回长度最短队列
}

/* 银行服务模拟：按指定的窗口数、服务总时间模拟银行业务。 */
void simulate(int numOfWin, int servTime) {
    Queue<Customer> *windows = new Queue<Customer>[numOfWin];
    for (int now = 0; now < servTime; now++) { // 在下班之前，每隔单位时间
        Customer c;
        c.time = 5 + rand() % 10; // 一位新顾客到达，其服务时长随机指定
        c.window = bestWindow(windows, numOfWin); // 找出最佳（最短）服务窗口
        windows[c.window].enqueue(c); // 新顾客加入对应的队列
        for (int i = 0; i < numOfWin; i++) { // 分别检查
            if (!windows[i].empty()) // 各非空队列
                if (--windows[i].front().time <= 0) // 队首顾客接受服务
                    windows[i].dequeue(); // 服务完毕则出列，由后继顾客接替
        }
        printWindows(windows, numOfWin, servTime - now);
    } //for
    delete[] windows; // 释放所有队列
}

template<typename T> void testQueue(Queue<T> myQueue) {
    /* 初始化队列 */
    printf("初始化队列：\n");
    printf("[1] 请输入队列中初始元素的个数：");
    int length;
    cin >> length;
    printf("[2] 请输入%d个初始元素：", length);
    T temp;
    for (int i = 0; i < length; i++) {
        cin >> temp;
        myQueue.enqueue(temp);
    }
    printf("[3] 队列初始化完成。当前队列中元素个数为：%d，队列中的元素为：", myQueue.size());
    cout << myQueue << '\n' << endl;

    /* 队列操作测试 */
    enum operationType {
        Enqueue, Dequeue, Front
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
            case Enqueue: {
                cout << prefixWhitespace << "入队操作。\n";
                cout << prefixWhitespace << "请输入入队的元素：";
                cin >> temp;

                cout << prefixOut;
                myQueue.enqueue(temp);
                printf("入队操作完成。\n");
                break;
            }
            case Dequeue: {
                cout << prefixWhitespace << "出队操作。\n";

                cout << prefixOut;
                if (!myQueue.empty()) {
                    temp = myQueue.dequeue();
                    printf("出队操作完成，出队的队首元素为：");
                    cout << temp << endl;
                } else {
                    printf("出队操作失败，当前队列为空。\n");
                }
                break;
            }
            case Front: {
                cout << prefixWhitespace << "队首操作。\n";

                cout << prefixOut;
                if (!myQueue.empty()) {
                    temp = myQueue.front();
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
        printf("当前队列中元素个数为：%d，队列中的元素为：", myQueue.size());
        cout << myQueue << '\n' << endl;
    }
}

int main() {
    Queue<int> myQueue;

    enum operationType {
        TestQueue, Simulate
    };
    cout << "请输入要执行的操作（01.队列测试 02.银行服务模拟）：";
    int opType;
    cin >> opType;
    switch (--opType) {
        case TestQueue:
            testQueue(myQueue);
            break;
        case Simulate:
            simulate(6, 300);
            break;
        default:
            cout << "输入的操作数错误。" << endl;
    }

    return 0;
}