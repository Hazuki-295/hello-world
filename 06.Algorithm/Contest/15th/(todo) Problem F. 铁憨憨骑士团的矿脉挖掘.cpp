#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, query;
    scanf("%d%d%d", &n, &m, &query);

    int matrix[n + 1][m + 1];
    int prefixSum[n + 1][m + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
            prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + matrix[i][j];
        }
    }

    int rangeSum[n + 1][m + 1][n + 1][m + 1];
    for (int x1 = 1; x1 <= n; x1++) {
        for (int y1 = 1; y1 <= m; y1++) {
            for (int x2 = x1; x2 <= n; x2++) {
                for (int y2 = y1; y2 <= m; y2++) {
                    rangeSum[x1][y1][x2][y2] =
                            prefixSum[x2][y2] - prefixSum[x1 - 1][y2] - prefixSum[x2][y1 - 1] +
                            prefixSum[x1 - 1][y1 - 1];
                }
            }
        }
    }

    int abs_last_ans = 0;
    while (query--) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 = x1 ^ abs_last_ans;
        y1 = y1 ^ abs_last_ans;
        x2 = x2 ^ abs_last_ans;
        y2 = y2 ^ abs_last_ans;

        int ans = numeric_limits<int>::min();
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                for (int p = i; p <= x2; p++) {
                    for (int q = j; q <= y2; q++) {
                        if (rangeSum[i][j][p][q] > ans) {
                            ans = rangeSum[i][j][p][q];
                        }
                    }
                }
            }
        }

        printf("%d\n", ans);
        abs_last_ans = abs(ans);
    }
    return 0;
}