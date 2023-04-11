#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, left, right;
    scanf("%d%d%d", &n, &left, &right);

    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }

    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
        c[i] = i;
    }

    int k = right - left + 1;
    vector<int> ordered_indexes;
    vector<int> ordered_numbers;
    ordered_indexes.reserve(k);
    ordered_numbers.reserve(k);

    for (int i = 1; i <= n; i++) {
        int b_i = b[i];
        if (b_i >= left && b_i <= right) {
            ordered_indexes.push_back(i);
            ordered_numbers.push_back(c[i]);
        }
    }
    sort(ordered_numbers.begin(), ordered_numbers.end());
    for (auto index: ordered_indexes) {
        c[index] = ordered_numbers[b[index] - left];
    }

    /* c = a[b[i]], b[i] is constant, a[i] is a permutation of [1, 2, ..., n] */
    for (int i = 1; i <= n - 1; i++) {
        printf("%d ", c[i]);
    }
    printf("%d\n", c[n]);

    return 0;
}

/***********
(Case 1)
Input data:
3 2 3
3 2 1
Output data:
2 1 3

(Case 2)
Input data:
6 2 4
3 2 5 4 1 6
Output data:
2 1 3 4 5 6
***********/