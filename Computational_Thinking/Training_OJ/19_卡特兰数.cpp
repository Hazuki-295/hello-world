#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set<string> result;
public:
    void backtrack(string &A, string &B, string &C) {
        if (A.size() == 0 && B.size() == 0) { // 递归基，所有字符都已放入C
            result.insert(C); // 得到一个等价串
            return;
        }

        if (B.size() != 0) {
            char temp = B.back(); // 备份栈顶元素
            B.pop_back(); C.push_back(temp); backtrack(A, B, C); // 尝试
            B.push_back(temp); C.pop_back(); // 回溯
        }

        if (A.size() != 0) {
            /* A中栈顶元素出栈 */
            char temp = A.front(); A.erase(A.begin());

            /* 尝试并回溯 */
            B.push_back(temp); backtrack(A, B, C);
            B.pop_back(); A.insert(A.begin(), temp);
        }
    }

    bool exist(string &s) {
        return find(result.begin(), result.end(), s) != result.end();
    }
};

int main() {
    int cases = 0;
    string str, s;
    while (cin >> str >> s) {
        Solution *obj = new Solution();
        string B, C;
        obj->backtrack(str, B, C);

        cout << "Case " << ++cases << ": ";
        cout << (obj->exist(s) ? "Yes" : "No") << endl;
    }
    return 0;
}
