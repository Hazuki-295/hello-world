#include <iostream>
#include <string>
using namespace std;

struct studentInfo {
    int id = 0;
    string name;
    studentInfo* next = nullptr;

    studentInfo() = default;
    studentInfo(int id, string name, studentInfo* next) : id(id), name(name), next(next) {}  // 本文件未使用的构造函数
};

int main() {
    studentInfo stu, *p, *q;

    /* 访问结构体内的元素，三种方式： */
    stu.id = 233;
    stu.name = "Bob";
    stu.next = p = new studentInfo;

    (*p).id = 255;
    (*p).name = "Alice";
    (*p).next = q = new studentInfo;

    q->id = 277;
    q->name = "Peter";
    q->next = nullptr;

    /* 使用指向结构体的指针时，后两种写法是完全等价的 */

    int count = 0;
    for (studentInfo* p = &stu; p != nullptr; p = p->next) {
        cout << "student" << (++count) << ": id = " << p->id << ", name = " << p->name << endl;
    }

    return 0;
}
