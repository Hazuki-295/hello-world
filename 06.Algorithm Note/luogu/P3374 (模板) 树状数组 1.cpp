#include <bits/stdc++.h>

/* Least Significant Bit of x having a value of 1. */
#define lowbit(x) ((x) & -(x))

using namespace std;

class FenwickTree {
private:
    vector<int> bit; // binary indexed tree
    size_t n;

public:
    FenwickTree(const vector<int> &array, int n) {
        this->n = n;
        bit.resize(n + 1);
        for (size_t i = 1; i <= array.size(); i++) {
            add(i, array[i]);
        }
    }

    void add(size_t index, int delta) {
        for (; index <= n; index += lowbit(index)) {
            bit[index] += delta;
        }
    }

    int prefixSum(size_t right) {
        int result = 0;
        for (; right > 0; right -= lowbit(right)) {
            result += bit[right];
        }
        return result;
    }

    int query(size_t left, size_t right) {
        return prefixSum(right) - prefixSum(left - 1);
    }
};

int main() {
    int n, query;
    scanf("%d%d", &n, &query);

    vector<int> array(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &array[i]);
    }
    FenwickTree bit(array, n);

    while (query--) {
        int op;
        scanf("%d", &op);
        switch (op) {
            case 1:
                int index, delta;
                scanf("%d%d", &index, &delta);
                bit.add(index, delta);
                break;
            case 2:
                int left, right;
                scanf("%d%d", &left, &right);
                printf("%d\n", bit.query(left, right));
                break;
            default:
                assert(false);
        }
    }

    return 0;
}