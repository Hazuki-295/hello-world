#include <vector>

using namespace std;

class NumMatrix {
public:
    vector<vector<int>> prefixSum; // prefixSum[i + 1][j + 1] = matrix[0][0] + ... + matrix[i][j], prefixSum[0][0] = 0

    NumMatrix(vector<vector<int>> &matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        prefixSum.resize(m + 1, vector<int>(n + 1));
        /* preprocessing, calculating prefix sum */
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefixSum[i + 1][j + 1] = prefixSum[i][j + 1] + prefixSum[i + 1][j] - prefixSum[i][j] + matrix[i][j];
                // prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + matrix[i][j] (for array index 1:n)
            }
        }
    }

    int sumRegion(int x1, int y1, int x2, int y2) {
        return prefixSum[x2 + 1][y2 + 1] - prefixSum[x1][y2 + 1] - prefixSum[x2 + 1][y1] + prefixSum[x1][y1];
        // prefixSum[x2][y2] - prefixSum[x1 - 1][y2] - prefixSum[x2][y1 - 1] + prefixSum[x1 - 1][y1 - 1] (for array index 1:n)
    }
};