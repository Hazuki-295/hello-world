#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> weights(n + 1);
    vector<int> prefixSum(n + 1);
    prefixSum[0] = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &weights[i]);
        prefixSum[i] = prefixSum[i - 1] + weights[i];
    }

    int min_diff = numeric_limits<int>::max();
    for (int middle = 2; middle <= n; middle++) {
        int left = prefixSum[middle - 1];
        int right = prefixSum[n] - prefixSum[middle - 1];
        int diff = abs(left - right);
        min_diff = min(diff, min_diff);
    }

    printf("%d\n", min_diff);

    return 0;
}