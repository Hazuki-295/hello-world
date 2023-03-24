#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void update_diff(vector<vector<int>> &diff, int x, int y, int c, int n) {
    int xl = max(x - c, 0), xr = min(x + c, n - 1);
    int yl = max(y - c, 0), yr = min(y + c, n - 1);
    for (int i = xl; i <= xr; i++) {
        for (int j = yl; j <= yr; j++) {
            int d = c - (abs(i - x) + abs(j - y));
            if (d > 0) {
                diff[i][j] ^= d;
            }
        }
    }
}

int calculate_xor_sum(int n, int m, const vector<vector<int>> &operations) {
    vector<vector<int>> diff(n, vector<int>(n, 0));
    for (int k = 0; k < m; k++) {
        int x = operations[k][0], y = operations[k][1], c = operations[k][2];
        update_diff(diff, x, y, c, n);
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res ^= diff[i][j];
        }
    }
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> operations(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        cin >> operations[i][0] >> operations[i][1] >> operations[i][2];
    }
    int res = calculate_xor_sum(n, m, operations);
    cout << res << endl;
    return 0;
}