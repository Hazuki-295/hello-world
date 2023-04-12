#include <bits/stdc++.h>

using namespace std;

inline int read() { // quickly read inputs
    int x = 0, sign = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * sign;
}

int main() {
    int n = read(), m = read();

    vector<int> Log2(n + 1);
    for (int i = 2; i <= n; i++) {
        Log2[i] = Log2[i >> 1] + 1;
    }

    /* Preprocessing, compute the sparse table. */
    vector<vector<int>> f(n + 1, vector<int>(Log2[n] + 1));
    for (int i = 1; i <= n; i++) {
        f[i][0] = read();
    }
    for (int j = 1; j <= Log2[n]; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        } // The max value in an interval of length 2^j, is the maximum of two max values in intervals of length 2^(j - 1).
    }

    /* Perform m interval queries on the array. */
    for (int i = 1; i <= m; i++) {
        int left = read(), right = read();
        int s = Log2[right - left + 1]; // Tow intervals of length 2^s must cover the interval being queried.
        printf("%d\n", max(f[left][s], f[right - (1 << s) + 1][s]));
    }

    return 0;
}