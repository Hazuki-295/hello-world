#include <vector>

using namespace std;

class NumMatrix {
public:
    vector<vector<int>> prefixSums; // prefixSums[i + 1][j + 1] = matrix[0][0] + ... + matrix[i][j], prefixSums[0][0] = 0

    NumMatrix(vector<vector<int>> &matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        prefixSums.resize(m + 1, vector<int>(n + 1));
        /* preprocessing, calculating prefix sums */
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefixSums[i + 1][j + 1] = prefixSums[i][j + 1] + prefixSums[i + 1][j] - prefixSums[i][j] + matrix[i][j];
                // prefixSums[i][j] = prefixSums[i - 1][j] + prefixSums[i][j - 1] - prefixSums[i - 1][j - 1] + matrix[i][j] (for array index 1:n)
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return prefixSums[row2 + 1][col2 + 1] - prefixSums[row1][col2 + 1] - prefixSums[row2 + 1][col1] + prefixSums[row1][col1];
        // prefixSums[row2][col2] - prefixSums[row1 - 1][col2] - prefixSums[row2][col1 - 1] + prefixSums[row1 - 1][col1 - 1] (for array index 1:n)
    }
};