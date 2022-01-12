#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
	bool validateStackSequences(string &pushed, string &popped) {
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

int main()
{
	int cases = 0; string pushed, popped;
	while (cin >> pushed >> popped) {
		cout << "Case " << ++cases << ": ";
		Solution *obj = new Solution;

		if (obj->validateStackSequences(pushed, popped))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}
