#include <iostream>
#include <string>
#include <vector>

using namespace std;

void buildNext(string T, vector<int> &next) {
    int length = T.size();

    next.resize(length + 1);    // 串及next数组的序号均为1~n
    T.insert(T.begin(), ' ');

    int j = 0;   // "主"串指针
    int i = 1;   // 模式串指针
    next[1] = 0; // next[1]设置为0，0号字符为通配符

    while (i < length) { // 需求出数组其余n-1项
        if (j == 0 || T[i] == T[j]) { // 匹配
            i++;
            j++;    // 下一匹配位置
            next[i] = j; // 一旦发现P[j]与P[i]匹配(含P[j = 0]的通配)，则可令 next[j+1](新的一项)=next[j](else分支得到)+1
        } else {
            j = next[j]; // 失配
        }
    }
}

void buildNextval(string T, vector<int> &nextval) {
    int length = T.size();

    nextval.resize(length + 1);    // 串及next数组的序号均为1~n
    T.insert(T.begin(), ' ');

    int j = 0;   // "主"串指针
    int i = 1;   // 模式串指针
    nextval[1] = 0; // next[1]设置为0，0号字符为通配符

    while (i < length) { // 需求出数组其余n-1项
        if (j == 0 || T[i] == T[j]) { // 匹配
            i++;
            j++;
            nextval[i] = (T[i] != T[j] ? j : nextval[j]); // 吸取教训
        } else { // 失配
            j = nextval[j];
        }
    }
}

int main() {

    cout << "请输入字符串：";
    string test;
    cin >> test; // ababcaab

    vector<int> next, nextval;
    buildNext(test, next);
    buildNextval(test, nextval);

    cout << "next数组：\t";
    for (size_t i = 1; i < next.size(); i++) {
        cout << next[i] << " ";
    }
    cout << endl;

    cout << "nextval数组：\t";
    for (size_t i = 1; i < nextval.size(); i++) {
        cout << nextval[i] << " ";
    }
    cout << endl;
}
