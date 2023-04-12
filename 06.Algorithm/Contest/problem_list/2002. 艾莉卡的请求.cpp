#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n, k;
        cin >> n >> k;

        vector<size_t> values(n + 1);
        vector<size_t> prefixSum(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> values[i];
            prefixSum[i] = prefixSum[i - 1] + values[i];
        }

        size_t ans = 0;
        int num_of_left = k, num_of_right = 0;
        while (num_of_left >= 0) {
            size_t sum_of_left = prefixSum[num_of_left];
            size_t sum_of_right = prefixSum[n] - prefixSum[n - num_of_right];
            size_t total_sum = sum_of_left + sum_of_right;
            if (total_sum > ans) {
                ans = total_sum;
            }
            num_of_left--;
            num_of_right++;
        }
        cout << ans << '\n';
    }

    return 0;
}