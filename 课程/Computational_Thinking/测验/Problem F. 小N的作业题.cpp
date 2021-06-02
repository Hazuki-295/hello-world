#include <iostream>
#include <vector>
using namespace std;

/* 二维前缀和方法。检索一次的时间复杂度为O(1)。 */
class NumMatrix {
public:
	vector<vector<int>> sums; // m+1 行 n+1 列，存放矩阵的二维前缀和。sums[i+1][j+1] 的值为 f(i, j) 的值。

	NumMatrix(vector<vector<int>> &matrix) { // 计算二维前缀和
		int m = matrix.size();    // 矩阵行数m
		if (m == 0) return;
		int n = matrix[0].size(); // 矩阵列数n
		sums.resize(m + 1, vector<int>(n + 1)); // 方便计算 sumRegion
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

int main()
{
	vector<vector<int>> grass;
	int grassNum; cin >> grassNum;
	grass.resize(2000 + 1, vector<int>(2000 + 1));
	int x, y, w;
	for (int i = 0; i < grassNum; i++) {
		cin >> x >> y >> w;
		grass[x][y] += w;
	}

	int searchNum; cin >> searchNum;
	int x1, y1, x2, y2;
	NumMatrix *obj = new NumMatrix(grass);
	for (int i = 0; i < searchNum; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		cout << obj->sumRegion(x1, y1, x2, y2) << endl;
	}
	return 0;
}
