#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
	bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
		int lengthPush = pushed.size();
		int lengthPop = popped.size();

		if (lengthPop != lengthPush) {
			return false;
		}

		int index = 0; // 出栈序列下标
		stack<int> stack;
		for (int i = 0; i < lengthPush; i++) { // 模拟进出栈
			stack.push(pushed[i]);
			while (!stack.empty() && stack.top() == popped[index]) { // 是待出栈元素
				stack.pop();
				index++;
			}
		}
		return stack.empty();
	}
};