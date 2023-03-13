#include <iostream>
#include <algorithm>
#include <sstream>
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
    /* r is a list of revenues where r[i] is the maximum revenue for selling a rod of length i, and r[0] = 0. */
    static int memoized_cut_rod(vector<int> &prices, int n) {
        vector<int> revenues(n + 1, -1); // will remember solution values in r
        return memoized_cut_rod_aux(prices, n, revenues);
    }

    static int memoized_cut_rod_aux(vector<int> &prices, int n, vector<int> &revenues) {
        if (revenues[n] >= 0) { // already have a solution for length n?
            return revenues[n];
        }

        /* Compute q like in cut_rod. */
        if (n == 0) return 0;

        int q = -1;
        for (int i = 1; i <= n; i++) { // i is the position of the first cut
            q = max(q, prices[i] + memoized_cut_rod_aux(prices, n - i, revenues));
        }
        revenues[n] = q; // remember the solution value for length n
        return q;
    }
};

/* Bottom-up implementation of cut_rod. */
int bottom_up_cut_rod(vector<int> &prices, int n) {
    vector<int> revenues(n + 1);

    revenues[0] = 0;
    for (int j = 1; j <= n; j++) { // solve each sub-problem of size j in order of increasing size
        int q = -1;
        for (int i = 1; i <= j; i++) { // same approach as cut rod, except that now directly reference array entry
            q = max(q, prices[i] + revenues[j - i]);
        }
        revenues[j] = q;
    }
    return revenues[n];
}

/* Compute maximum revenue and optimal size of first piece cut off. */
class Extended_Bottom_Up_Cut_Rod {
public:
    static pair<vector<int>, vector<int>> extended_bottom_up_cut_rod(vector<int> &price, int n) {
        vector<int> revenues(n + 1);
        vector<int> sizes(n + 1); // optimal cut locations, solution[0] is not used

        revenues[0] = 0;
        for (int j = 1; j <= n; j++) { // for increasing rod length j
            int q = -1;
            for (int i = 1; i <= j; i++) { // i is the position of the first cut
                if (q < price[i] + revenues[j - i]) {
                    q = price[i] + revenues[j - i];
                    sizes[j] = i; // best cut location so far for length j
                }
            }
            revenues[j] = q; // remember the solution value for length j
        }
        return make_pair(revenues, sizes);
    }

    /* Print how far apart to cut, which is an optimal solution to rod-cutting problem with rod length n. */
    static void print_cut_rod_solution(vector<int> &price, int n) {
        auto result = extended_bottom_up_cut_rod(price, n);
        vector<int> revenues = result.first;
        vector<int> sizes = result.second;
        printf("r%d = %d from solution %d = ", n, revenues[n], n);
        stringstream output;
        while (n > 0) {
            output << sizes[n] << " + "; // cut location for length n
            n -= sizes[n]; // length of the remainder of the rod
        }
        string solution = output.str();
        solution = solution.substr(0, solution.length() - 3);
        cout << solution << endl;
    }
};

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
    // Extended bottom up cut rod.
    cout << "Extended bottom up cut rod:\n";
    Extended_Bottom_Up_Cut_Rod::print_cut_rod_solution(prices, 4);  // should be 2, 2
    Extended_Bottom_Up_Cut_Rod::print_cut_rod_solution(prices, 7);  // should be 1, 6 or 2, 2, 3
    Extended_Bottom_Up_Cut_Rod::print_cut_rod_solution(prices, 10); // should be 10

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
    // Extended bottom up cut rod.
    cout << "Extended bottom up cut rod:\n";
    Extended_Bottom_Up_Cut_Rod::print_cut_rod_solution(prices, 18);
    Extended_Bottom_Up_Cut_Rod::print_cut_rod_solution(prices, prices.size());

    return 0;
}