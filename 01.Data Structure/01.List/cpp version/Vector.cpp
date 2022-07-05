#include <iostream>
#include "Vector.h"

using namespace std;

template<typename T>
void permute(Vector<T> &V) { // 随机置乱向量，使各元素等概率出现于各位置
    for (int i = V.size(); i > 0; i--) {    // 自后向前
        std::swap(V[i - 1], V[rand() % i]); // 将V[i - 1]与V[0, i)中某一元素随机交换
    }
}

template<typename T>
struct Increase { // 函数对象：递增一个T类对象
    virtual void operator()(T &e) { e++; } // 假设T可直接递增，或已重载++
};

template<typename T>
void increase(Vector<T> &V) {  // 统一递增向量的各元素
    V.traverse(Increase<T>()); // 以Increase<T>()为基本操作进行遍历
}

template<typename T>
void print(Vector<T> &V) { // 打印向量
    cout << '[';
    for (int i = 0; i < V.size() - 1; i++) {
        cout << V[i] << ", ";
    }
    cout << V[V.size() - 1] << ']';
}

int main() {
    using T = char;
    Vector<T> myVector;

    srand((unsigned int) time(NULL)); // 设置随机数种子

    /* 初始化向量 */
    printf("初始化向量：\n");
    printf("[1] 请输入向量中初始元素的个数：");
    int length;
    cin >> length;
    printf("[2] 请输入%d个初始元素：", length);
    T temp;
    for (int i = 0; i < length; i++) {
        cin >> temp;
        myVector.insert(temp);
    }
    printf("[3] 向量初始化完成。当前向量长度为：%d，向量中的元素为：", myVector.size());
    print(myVector);
    printf("\n\n");

    /* 向量操作测试 */
    enum operationType {
        Insert, Remove, Find, Sort, Permute, Deduplicate
    };
    printf("向量操作测试：\n");
    int caseCount = 0, opType;
    while (true) {
        string prefixIn = "In [" + to_string(++caseCount) + "]: ";
        string prefixOut = "Out[" + to_string(caseCount) + "]: ";
        string prefixWhitespace = string(prefixIn.length(), ' ');

        cout << prefixIn;
        printf("请输入将要执行的操作（01.插入 02.删除 03.按值查找 04.排序 05.随机置乱 06.整体去重）：");
        if (scanf("%d", &opType) == EOF) {
            printf("\n\n");
            break;
        }
        switch (--opType) {
            case Insert: {
                cout << prefixWhitespace << "插入操作。\n";
                cout << prefixWhitespace << "请输入插入的位置：";
                int insertPos;
                cin >> insertPos;
                cout << prefixWhitespace << "请输入插入的元素：";
                cin >> temp;

                cout << prefixOut;
                if (insertPos >= 1 && insertPos <= myVector.size() + 1) {
                    myVector.insert(insertPos - 1, temp);
                    printf("插入操作完成。\n");
                } else {
                    printf("插入失败。插入的位置非法。\n");
                }
                break;
            }
            case Remove: {
                cout << prefixWhitespace << "删除操作。\n";
                cout << prefixWhitespace << "请输入删除的位置：";
                int removePos;
                cin >> removePos;

                cout << prefixOut;
                if (removePos >= 1 && removePos <= myVector.size()) {
                    temp = myVector.remove(removePos - 1);
                    printf("删除操作完成。删除的元素的值为：");
                    cout << temp << endl;
                } else {
                    printf("删除失败。删除的位置非法。\n");
                }
                break;
            }
            case Find: {
                cout << prefixWhitespace << "按值查找操作。\n";
                cout << prefixWhitespace << "请输入要查找的值：";
                cin >> temp;

                cout << prefixOut;
                int pos = myVector.find(temp);
                if (pos != -1) {
                    printf("查找成功。最后一个值等于给定值的元素的位序为：%d\n", pos + 1);
                } else {
                    printf("查找失败。向量中不存在该元素。\n");
                }
                break;
            }
            case Sort: {
                cout << prefixWhitespace << "排序操作。\n";
                myVector.sort();

                cout << prefixOut;
                printf("排序操作完成。\n");
                break;
            }
            case Permute: {
                cout << prefixWhitespace << "随机置乱操作。\n";
                myVector.unsort();

                cout << prefixOut;
                printf("随机置乱操作完成。\n");
                break;
            }
            case Deduplicate: {
                cout << prefixWhitespace << "整体去重操作。\n";
                int numOfRemove = myVector.deduplicate();

                cout << prefixOut;
                printf("整体去重操作完成。删除的重复元素个数为：");
                cout << numOfRemove << endl;
                break;
            }
            default: {
                cout << prefixOut << "输入的操作数错误。" << endl;
            }
        }

        /* 当次操作后输出向量 */
        cout << prefixWhitespace;
        printf("当前向量长度为：%d，向量中的元素为：", myVector.size());
        print(myVector);
        printf("\n\n");
    }

    return 0;
}

