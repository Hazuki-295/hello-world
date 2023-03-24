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

    int sumRegion(int x1, int y1, int x2, int y2) {
        return prefixSums[x2 + 1][y2 + 1] - prefixSums[x1][y2 + 1] - prefixSums[x2 + 1][y1] + prefixSums[x1][y1];
        // prefixSums[x2][y2] - prefixSums[x1 - 1][y2] - prefixSums[x2][y1 - 1] + prefixSums[x1 - 1][y1 - 1] (for array index 1:n)
    }
};