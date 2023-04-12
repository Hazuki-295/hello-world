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

class SparseTable {
private:
    vector<vector<int>> f; // sparse table
    vector<int> Log2;

public:
    SparseTable(const vector<int> &nums) {
        int n = nums.size() - 1; // exclude nums[0] = 0

        Log2.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            Log2[i] = Log2[i >> 1] + 1;
        }

        /* Preprocessing, compute the sparse table. */
        f.assign(n + 1, vector<int>(Log2[n] + 1));
        for (int i = 1; i <= n; i++) {
            f[i][0] = nums[i];
        }
        for (int j = 1; j <= Log2[n]; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            } // The max value in an interval of length 2^j, is the maximum of two max values in intervals of length 2^(j - 1).
        }
    }

    int query(int left, int right) {
        int s = Log2[right - left + 1];
        return max(f[left][s], f[right - (1 << s) + 1][s]);
    } // Tow intervals of length 2^s must cover the interval being queried.
};

int main() {
    int n = read(), m = read();

    vector<int> nums(n + 1);
    for (int i = 1; i <= n; i++) {
        nums[i] = read();
    }
    SparseTable sparseTable(nums);

    /* Perform m interval queries on the array. */
    for (int i = 1; i <= m; i++) {
        int left = read(), right = read();
        printf("%d\n", sparseTable.query(left, right));
    }

    return 0;
}