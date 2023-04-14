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
            prefixSum[i][j] = prefixSum[i][j - 1] + matrix[i][j];
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
        for (int row1 = x1; row1 <= x2; row1++) {
            for (int row2 = row1; row2 <= x2; row2++) {
                for (int col1 = y1; col1 <= y2; col1++) {
                    for (int col2 = col1; col2 <= y2; col2++) {
                        int pre = numeric_limits<int>::min();
                        for (int i = row1; i <= row2; i++) {
                            int current = prefixSum[i][col2] - prefixSum[i][col1 - 1];
                            if (pre >= 0) {
                                pre += current;
                            } else {
                                pre = current;
                            }
                        }
                        ans = max(pre, ans);
                    }
                }
            }
        }

        printf("%d\n", ans);
        abs_last_ans = abs(ans);
    }
    return 0;
}