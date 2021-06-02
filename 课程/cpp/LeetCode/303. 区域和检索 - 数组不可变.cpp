#include <iostream>
#include <vector>
using namespace std;

class NumArray {
public:
	vector<int> sums; 
	// ǰ׺�����飬sums[i]��ʾ����nums���±�0���±�i-1��ǰ׺�͡�sums[0] = 0����ʵ������

	NumArray(vector<int> &nums) {
		int n = nums.size();
		sums.resize(n + 1); 
		// ����Ϊ n - 1��������� sumRange(i, j)
		for (int i = 0; i < n; i++) {        // �������� nums ����ǰ׺��
			sums[i + 1] = sums[i] + nums[i]; // nums[0 ~ i] = nums[0 ~ (i - 1)] + nums[i]
		}
	}

	int sumRange(int i, int j) {      // ÿ�μ���ֻ��Ҫ�õ������±괦��ǰ׺�ͣ�Ȼ������ֵ
		return sums[j + 1] - sums[i]; // sumRange(i, j) = nums[0 ~ j] - nums[0 ~ (i - 1)]
	}
};