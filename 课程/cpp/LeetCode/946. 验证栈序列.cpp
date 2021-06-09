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

		int index = 0; // ��ջ�����±�
		stack<int> stack;
		for (int i = 0; i < lengthPush; i++) { // ģ�����ջ
			stack.push(pushed[i]);
			while (!stack.empty() && stack.top() == popped[index]) { // �Ǵ���ջԪ��
				stack.pop();
				index++;
			}
		}
		return stack.empty();
	}
};