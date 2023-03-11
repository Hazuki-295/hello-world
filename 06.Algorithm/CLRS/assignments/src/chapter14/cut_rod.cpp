#include <iostream>
#include <vector>

using namespace std;

/* Native, recursive top-down implementation of cut_rod. */
int cut_rod(vector<int> &prices, int n) {
    if (n == 0) return 0; // Base case.

    int q = -1;
    for (int i = 1; i < n + 1; i++) {
        q = max(q, prices[i] + cut_rod(prices, n - i));
    }
    return q;
}


int main() {
    // Textbook example.
    vector<int> prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    // Standard cut rod.
    cout << "Standard cut rod:\n";
    cout << cut_rod(prices, 4) << '\n';   // should be 10
    cout << cut_rod(prices, 10) << '\n';  // should be 30

    return 0;
}