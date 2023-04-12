#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<string> result;
public:
    void backtrack(string A, string B, string C) {
        if (A.size() == 0 && B.size() == 0) { // 递归基，所有字符都已放入C
            result.push_back(C); // 得到一个等价串
            return;
        }

        /* B中栈顶元素出栈 */
        if (B.size() != 0) {
            backtrack(A, B.substr(0, B.size() - 1), C + B.back());
        }

        /* A中栈顶元素出栈 */
        if (A.size() != 0) {
            backtrack(A.substr(1, A.size()), B + A.front(), C);
        }
    }

    bool exist(string testValidOutput) {
        return find(result.begin(), result.end(), testValidOutput) != result.end();
    }
};

int main() {
    int cases = 0;
    string inputStr, testValidOutput;
    while (cin >> inputStr >> testValidOutput) {
        Solution *obj = new Solution();
        string B, C;
        obj->backtrack(inputStr, B, C);

        cout << "Case " << ++cases << ": ";
        cout << (obj->exist(testValidOutput) ? "Yes" : "No") << endl;
    }
    return 0;
}
