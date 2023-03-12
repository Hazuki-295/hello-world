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


int main() {
    /* Textbook example. */
    vector<int> prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    // Standard cut rod.
    cout << "Standard cut rod:\n";
    cout << cut_rod(prices, 4) << '\n';   // should be 10
    cout << cut_rod(prices, 10) << '\n';  // should be 30

    cout << endl;

    /* Larger example. */
    srand(time(NULL));

    int size = 40;
    prices = vector<int>(size);
    for (int i = 0; i < prices.size(); i++) {
        prices[i] = rand() % 100 + 1;
    }
    prices.push_back(0);                         // for length 0
    sort(prices.begin(), prices.end()); // sorted, unique prices
    prices.erase(unique(prices.begin(), prices.end()), prices.end());

    // Standard cut rod.
    cout << "Standard cut rod:\n";
    cout << cut_rod(prices, 18) << '\n';
    cout << cut_rod(prices, 10) << '\n';
    cout << cut_rod(prices, prices.size()) << '\n';

    return 0;
}