#include <bits/stdc++.h>

using namespace std;

inline int read() { // 快读
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
    vector<vector<int>> ST;
    vector<int> Log2;

public:
    SparseTable(const vector<int> &nums) {
        int length = nums.size();
        int log2_n = log2(length);

        Log2.resize(log2_n + 1);
        for (int i = 2; i <= log2_n; i++) {
            Log2[i] = Log2[i / 2] + 1;
        }

        ST.assign(length, vector<int>(log2_n, 0));
        for (int i = 0; i < length; ++i) {
            ST[i][0] = nums[i];
        }
        for (int j = 1; j < log2_n; ++j) {
            int pj = (1 << (j - 1));
            for (int i = 0; i + pj < length; ++i) {
                ST[i][j] = max(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int lt = r - l + 1;
        int q = ceil(log2(lt)) - 1;
        return max(ST[l][q], ST[r - (1 << q) + 1][q]);
    }
};

int main() {
    const int log2_n = 17;
    const int max_n = 1e5;

    int f[max_n][log2_n + 1] = {};
    int Log2[max_n + 1] = {};
    for (int i = 2; i <= max_n; i++) {
        Log2[i] = Log2[i / 2] + 1;
    }

    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
        f[i][0] = read();
    }

    for (int j = 1; j <= log2_n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }

    for (int i = 1; i <= m; i++) {
        int left = read(), right = read();
        int s = Log2[right - left + 1];
        printf("%d\n", max(f[left][s], f[right - (1 << s) + 1][s]));
    }

    return 0;
}