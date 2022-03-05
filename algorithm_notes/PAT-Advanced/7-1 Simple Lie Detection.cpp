#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* 7-1 Simple Lie Detection */

int judgement(int length, const string s) {
    int score = 0;

    /* 01. the string starts with an f has its score −2; */
    if (s[0] == 'f') {
        score -= 2;
    }

    /* 02. the string ends with an a has its score −1; */
    if (s[length - 1] == 'a') {
        score -= 1;
    }

    /* 03. for every longest segment of answeres where the same letter is chosen for consecutive questions,
    if the segment length is larger than 5, the score is to +3; */
    vector<string> rule3;
    for (int i = 0; i < length; i++) {  // 连续的字符，i为起点
        int count = 1;

        for (int j = i; j < length - 1; j++) {
            if (s[j] == s[j + 1]) {  // 匹配，右移
                count++;
            } else {  // 失配，退出循环
                break;
            }
        }

        // 不匹配或结尾时，退出循环，得到最长匹配子串
        if (count > 5) {
            rule3.push_back(s.substr(i, count));
        }
    }

    if (rule3.size() != 0) {
        int longest = rule3[0].length();
        for (auto s : rule3) {
            if (s.length() > longest) {
                longest = s.length();
            }
        }

        for (auto s : rule3) {
            if (s.length() == longest) {
                score += 3;
            }
        }
    }

    /* 04. if an a is immediately followed by e or h, the score is to −4; */
    for (int i = 0; i < length - 1; i++) {
        string temp = s.substr(i, 2);
        if (temp == string("ae") or temp == string("ah")) {
            score -= 4;
        }
    }

    /* 05. for every longest segment of answeres where consecutively increasing letters are chosen to answer
    consecutive questions (such as abcd or defgh), if the segment length is larger than 3, the score is to +5.*/
    vector<string> rule5;
    for (int i = 0; i < length; i++) {  // 连续的字符，i为起点
        int count = 1;

        for (int j = i; j < length - 1; j++) {
            if (s[j + 1] == (s[j] + 1)) {  // 匹配，右移
                count++;
            } else {  // 失配，退出循环
                break;
            }
        }

        // 不匹配或结尾时，退出循环，得到最长匹配子串
        if (count > 3) {
            rule5.push_back(s.substr(i, count));
        }
    }

    if (rule5.size() != 0) {
        int longest = rule5[0].length();
        for (auto s : rule5) {
            if (s.length() > longest) {
                longest = s.length();
            }
        }

        for (auto s : rule5) {
            if (s.length() == longest) {
                score += 5;
            }
        }
    }

    return score;
}

int main() {
    int N, T, K;
    cin >> N >> T >> K;  // 问题个数(即每个字符串的长度)、阈值、字符串个数

    vector<string> input;
    input.resize(K);
    for (int i = 0; i < K; i++) {  // 输入题目，对每一个字符串进行评分
        cin >> input[i];
        int score = judgement(N, input[i]);

        cout << score;
        if (score > T) {
            cout << "!!!";
        }
        cout << endl;
    }

    // abbcdeaeah

    return 0;
}