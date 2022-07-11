#include <iostream>
#include <string>
#include <vector>

using namespace std;

void buildNext(string T, vector<int> &next) {
    int length = T.size();

    next.resize(length + 1);    // ����next�������ž�Ϊ1~n
    T.insert(T.begin(), ' ');

    int j = 0;   // "��"��ָ��
    int i = 1;   // ģʽ��ָ��
    next[1] = 0; // next[1]����Ϊ0��0���ַ�Ϊͨ���

    while (i < length) { // �������������n-1��
        if (j == 0 || T[i] == T[j]) { // ƥ��
            i++;
            j++;    // ��һƥ��λ��
            next[i] = j; // һ������P[j]��P[i]ƥ��(��P[j = 0]��ͨ��)������� next[j+1](�µ�һ��)=next[j](else��֧�õ�)+1
        } else {
            j = next[j]; // ʧ��
        }
    }
}

void buildNextval(string T, vector<int> &nextval) {
    int length = T.size();

    nextval.resize(length + 1);    // ����next�������ž�Ϊ1~n
    T.insert(T.begin(), ' ');

    int j = 0;   // "��"��ָ��
    int i = 1;   // ģʽ��ָ��
    nextval[1] = 0; // next[1]����Ϊ0��0���ַ�Ϊͨ���

    while (i < length) { // �������������n-1��
        if (j == 0 || T[i] == T[j]) { // ƥ��
            i++;
            j++;
            nextval[i] = (T[i] != T[j] ? j : nextval[j]); // ��ȡ��ѵ
        } else { // ʧ��
            j = nextval[j];
        }
    }
}

int main() {

    cout << "�������ַ�����";
    string test;
    cin >> test; // ababcaab

    vector<int> next, nextval;
    buildNext(test, next);
    buildNextval(test, nextval);

    cout << "next���飺\t";
    for (size_t i = 1; i < next.size(); i++) {
        cout << next[i] << " ";
    }
    cout << endl;

    cout << "nextval���飺\t";
    for (size_t i = 1; i < nextval.size(); i++) {
        cout << nextval[i] << " ";
    }
    cout << endl;
}
