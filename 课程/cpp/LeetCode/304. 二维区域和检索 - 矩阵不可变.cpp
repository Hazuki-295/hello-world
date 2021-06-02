#include <iostream>
#include <vector>
using namespace std;

/* ��άǰ׺�ͷ���������һ�ε�ʱ�临�Ӷ�ΪO(1)�� */
class NumMatrix {
public:
	vector<vector<int>> sums; // m+1 �� n+1 �У���ž���Ķ�άǰ׺�͡�sums[i+1][j+1] ��ֵΪ f(i, j) ��ֵ��

	NumMatrix(vector<vector<int>> &matrix) { // �����άǰ׺��
		int m = matrix.size();    // ��������m
		if (m == 0) return;
		int n = matrix[0].size(); // ��������n
		sums.resize(m + 1, vector<int>(n + 1)); // ������� sumRegion
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] - sums[i][j] + matrix[i][j];
			} // f(i, j) = f(i-1, j) + f(i, j-1) - f(i-1, j-1) + matrix[i][j]
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return sums[row2 + 1][col2 + 1] - sums[row1][col2 + 1] - sums[row2 + 1][col1] + sums[row1][col1];
	} // f(row2, col2) - f(row1-1, col2) - f(row2, col1-1) + f(row1-1, col1-1)
};

/* һάǰ׺�ͷ���������ʱ���������������m��ʱ�临�Ӷ�ΪO(m)���ᳬʱ�� */
class NumMatrix {
public:
	vector<vector<int>> sums; // m �� n+1 �У���ž���ÿһ�е�һάǰ׺��

	NumMatrix(vector<vector<int>> &matrix) { // �Ծ����ÿһ�м���ǰ׺��
		int m = matrix.size();    // ��������m
		if (m == 0) return;
		int n = matrix[0].size(); // ��������n
		sums.resize(m, vector<int>(n + 1)); // ����Ϊ n + 1���������ÿһ�е�������� sumRange(i, j)
		for (int i = 0; i < m; i++) { // ����ÿһ�е�ǰ׺��
			for (int j = 0; j < n; j++) {
				sums[i][j + 1] = sums[i][j] + matrix[i][j]; // nums[0 ~ j] = nums[0 ~ (j-1)] + nums[j]
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		int sum = 0;
		for (int i = row1; i <= row2; i++) { // �Զ�ά�����е�ÿһ�м����������
			sum += sums[i][col2 + 1] - sums[i][col1]; // sumRange(i, j) = nums[0 ~ j] - nums[0 ~ (i - 1)]
		}
		return sum;
	}
};
