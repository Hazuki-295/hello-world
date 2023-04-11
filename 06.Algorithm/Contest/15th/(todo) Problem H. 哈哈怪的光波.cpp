#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int matrix[n + 1][n + 1] = {};
    for (int i = 0; i < m; i++) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        matrix[x][y] += c;
    }
    int ground[n + 1][n + 1] = {};
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            int c = matrix[i][j];
            if (c == 0) continue;
            ground[i][j] += c;
            int row = i;
            int col_left = j;
            int col_right = j;
            while (c-- >= 1) {
                if (row-- >= 1) {
                    col_left--;
                    col_right++;
                    if (col_left >= 1 && col_right <= n) {
                        for (int col = col_left; col <= col_right; col++) {
                            ground[row][col] += c;
                        }
                    }
                }
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            result ^= ground[i][j];
        }
    }
    printf("%d", result);

    return 0;
}