#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/* Native, recursive top-down implementation of cut_rod. */
int cut_rod(vector<int> &prices, int n) {
    if (n == 0) return 0; // Base case.

    int q = -1;
    for (int i = 1; i <= n; i++) {
        q = max(q, prices[i] + cut_rod(prices, n - i));
    }
    return q;
}

/* Recursive top-down with memoization implementation of cut_rod. */
class Memoized_Cut_Rod {
public:
    static int memoized_cut_rod(vector<int> &prices, int n) {
        vector<int> remember(n + 1, -1); // will remember solution values in r
        return memoized_cut_rod_aux(prices, n, remember);
    }

    static int memoized_cut_rod_aux(vector<int> &prices, int n, vector<int> &remember) {
        if (remember[n] >= 0) { // already have a solution for length n?
            return remember[n];
        }

        /* Compute q like in cut_rod. */
        if (n == 0) return 0; // Base case.

        int q = -1;
        for (int i = 1; i <= n; i++) { // i is the position of the first cut
            q = max(q, prices[i] + memoized_cut_rod_aux(prices, n - i, remember));
        }
        remember[n] = q; // remember the solution value for length n
        return q;
    }
};

/* Bottom-up implementation of cut_rod. */
int bottom_up_cut_rod(vector<int> &prices, int n) {
    vector<int> remember(n + 1);

    remember[0] = 0;
    for (int j = 1; j <= n; j++) { // solve each sub-problem of size j in order of increasing size
        int q = -1;
        for (int i = 1; i <= j; i++) { // same approach as memoized cut rod, but directly references array entry
            q = max(q, prices[i] + remember[j - i]);
        }
        remember[j] = q;
    }
    return remember[n];
}


int main() {
    /* Textbook example. */
    vector<int> prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    // Standard cut rod.
    cout << "Standard cut rod:\n";
    cout << cut_rod(prices, 4) << '\n';   // should be 10
    cout << cut_rod(prices, 10) << '\n';  // should be 30
    // Memoized cut rod.
    cout << "Memoized cut rod:\n";
    cout << Memoized_Cut_Rod::memoized_cut_rod(prices, 4) << '\n';   // should be 10
    cout << Memoized_Cut_Rod::memoized_cut_rod(prices, 10) << '\n';  // should be 30
    // Bottom up cut rod.
    cout << "Bottom up cut rod:\n";
    cout << bottom_up_cut_rod(prices, 4) << '\n';   // should be 10
    cout << bottom_up_cut_rod(prices, 10) << '\n';  // should be 30

    cout << endl;

    /* Larger example. */
    srand(time(NULL));

    int size = 30;
    prices = vector<int>(size);
    for (int i = 0; i < prices.size(); i++) {
        prices[i] = rand() % 100 + 1;
    }
    prices.push_back(0);                         // for length 0
    sort(prices.begin(), prices.end()); // sorted, unique prices
    prices.erase(unique(prices.begin(), prices.end()), prices.end());

    cout << "Vector Size: " << prices.size() << '\n' << "[ ";
    for (int i = 0; i < prices.size(); i++) {
        cout << prices[i] << ' ';
    }
    cout << ']' << '\n' << endl;

    // Standard cut rod.
    cout << "Standard cut rod:\n";
    cout << cut_rod(prices, 18) << '\n';
    cout << cut_rod(prices, prices.size()) << '\n';
    // Memoized cut rod.
    cout << "Memoized cut rod:\n";
    cout << Memoized_Cut_Rod::memoized_cut_rod(prices, 18) << '\n';
    cout << Memoized_Cut_Rod::memoized_cut_rod(prices, prices.size()) << '\n';
    // Bottom up cut rod.
    cout << "Bottom up cut rod:\n";
    cout << bottom_up_cut_rod(prices, 18) << '\n';
    cout << bottom_up_cut_rod(prices, prices.size()) << '\n';

    return 0;
}