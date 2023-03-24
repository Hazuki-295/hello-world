#include <iostream>

int main() {
    int n, m, query;
    scanf("%d%d%d", &n, &m, &query);
    int matrix[n + 1][m + 1];
    int values[n + 1][m + 1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
            values[i][j] = values[i - 1][j] + values[i][j - 1] - values[i - 1][j - 1] + matrix[i][j];
        }
    }
    int abs_last_ans = 0;
    for (int i = 0; i < query; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 = (x1 ^ abs_last_ans) % (n + 1);
        y1 = (y1 ^ abs_last_ans) % (m + 1);
        x2 = (x2 ^ abs_last_ans) % (n + 1);
        y2 = (y2 ^ abs_last_ans) % (m + 1);
        for (int row = x1; row <= x2; row++) {
            for (int col = y1; col <= y2; col++) {

            }
        }
        int ans = values[x2][y2] - values[x2][y1 - 1] - values[x1 - 1][y2] + values[x1 - 1][y1 - 1];
        printf("%d\n", ans);
        abs_last_ans = abs(ans);
    }
    return 0;
}