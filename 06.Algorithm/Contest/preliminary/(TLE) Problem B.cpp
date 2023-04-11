#include <bits/stdc++.h>

using namespace std;

int n, left, right;
vector<int> b;

vector<vector<int>> result_permutations;

bool construct_array(deque<int> &unselected, vector<int> &selected_ordered_indexes, vector<int> &a) {
    if (unselected.empty()) {
        result_permutations.push_back(a);
        return true;
    }

    int b_i = b[n - unselected.size() + 1];
    for (int i = 0; i < unselected.size(); i++) {
        int selected_num = unselected[i];
        /* Pruning branch, test whether meet the constraint. */
        if (b_i >= ::left && b_i <= ::right) { // numbers is ordered, limited
            for (auto selected_ordered_index: selected_ordered_indexes) {
                if (b_i < selected_ordered_index && selected_num > a[selected_ordered_index]) {
                    return false;
                }
                if (b_i > selected_ordered_index && selected_num < a[selected_ordered_index]) {
                    return false;
                }
            }
        }
        /* Backup before traceback. */
        deque<int> unselected_back = unselected;
        vector<int> selected_ordered_indexes_back = selected_ordered_indexes;
        vector<int> a_back = a;

        /* Have a try. */
        unselected_back.erase(unselected_back.begin() + i);
        a_back[b_i] = selected_num;
        if (b_i >= ::left && b_i <= ::right) {
            selected_ordered_indexes_back.push_back(b_i);
        }
        construct_array(unselected_back, selected_ordered_indexes_back, a_back);
    }

    return false;
}

int main() {
    //int n, left, right;
    scanf("%d%d%d", &n, &::left, &::right);

    //vector<int> b(n + 1);
    b.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }

    deque<int> unselected(n);
    for (int i = 0; i < n; i++) {
        unselected[i] = i + 1;
    }
    vector<int> selected_ordered_indexes;

    vector<int> a(n + 1);
    construct_array(unselected, selected_ordered_indexes, a);
    vector<int> result_a = result_permutations[0];

    /* c = a[b[i]], b[i] is constant, a[i] is a permutation of [1, 2, ..., n] */
    for (int i = 1; i <= n - 1; i++) {
        printf("%d ", result_a[b[i]]);
    }
    printf("%d\n", result_a[b[n]]);

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