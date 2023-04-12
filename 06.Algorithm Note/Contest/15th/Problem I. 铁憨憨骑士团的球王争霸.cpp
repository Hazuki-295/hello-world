#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> weights(pow(2, n));
    for (int i = 0; i < weights.size(); i++) {
        scanf("%d", &weights[i]);
    }

    int myself = weights[0];
    sort(weights.begin(), weights.end());
    size_t my_rank = find(weights.begin(), weights.end(), myself) - weights.begin() + 1;

    int ans = log2(my_rank) + (my_rank == weights.size() ? 0 : 1);

    printf("%d", ans);

    return 0;
}