#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    int prefix_xor[n + 1];
    int prefix_xor_watered[n + 1];
    prefix_xor[0] = prefix_xor_watered[0] = 0;

    for (int i = 1; i <= n; i++) {
        int value;
        scanf("%d", &value);

        prefix_xor[i] = prefix_xor[i - 1] ^ value;
        prefix_xor_watered[i] = prefix_xor_watered[i - 1] ^ (value + 1);
    }

    int ans = prefix_xor[n];
    for (int begin = 1; begin <= n; begin++) {
        for (int end = begin; end <= n; end++) {
            int exclude_part = prefix_xor[end] ^ prefix_xor[begin - 1];
            int include_part = prefix_xor_watered[end] ^ prefix_xor_watered[begin - 1];
            int result = prefix_xor[n] ^ exclude_part ^ include_part;
            ans = max(ans, result);
        }
    }
    printf("%d\n", ans);

    return 0;
}