#include <iostream>
#include <vector>
#include "print_table.h"

using namespace std;

wchar_t UP_AND_LEFT = L'\u2196';  // northwest arrow
wchar_t UP = L'\u2191';           // up arrow
wchar_t LEFT = L'\u2190';         // left arrow

class LCS_Length {
private:
    string X, Y;
    int m, n;

    vector<vector<int>> c; // c[i, j] is the length of an LCS of the sequences X[:i] and Y[:j].
    vector<vector<wchar_t>> b; // b[i, j] points to the table entry corresponding to the optimal sub-problem solution chosen when computing c[i, j].

public:
    /* Recursively compute the length of an LCS of two sequences. */
    LCS_Length(string &X, string &Y, int m, int n) : X(X), Y(Y), m(m), n(n) {
        c = vector<vector<int>>(m + 1, vector<int>(n + 1));         // using indices c[0:m, 0:n]
        b = vector<vector<wchar_t>>(m + 1, vector<wchar_t>(n + 1)); // using indices b[1:m, 1:n]

        for (int i = 0; i <= m; i++) { // j = 0
            c[i][0] = 0;
        }
        for (int j = 0; j <= n; j++) { // i = 0
            c[0][j] = 0;
        }
        for (int i = 1; i <= m; i++) { // compute table entries in row-major order
            for (int j = 1; j <= n; j++) {
                /* Sub-problem of finding LCS of X[: i-1] and Y[: j-1]. */
                if (X[i - 1] == Y[j - 1]) {
                    c[i][j] = c[i - 1][j - 1] + 1;
                    b[i][j] = UP_AND_LEFT;
                } else if (c[i - 1][j] >= c[i][j - 1]) { // Consider two sub-problems, store max(c[i, j-1], c[i-1, j]).
                    c[i][j] = c[i - 1][j];
                    b[i][j] = UP;
                } else {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = LEFT;
                }
            }
        }
    }

    /* Print an LCS of X and Y in the proper, forward order. */
    void print_lcs(int i, int j) {
        if (i == 0 || j == 0) // the LCS has length 0
            return;
        /* Follow directions to print in proper, forward order. */
        if (b[i][j] == UP_AND_LEFT) {
            print_lcs(i - 1, j - 1);
            cout << X[i - 1];
        } else if (b[i][j] == UP) {
            print_lcs(i - 1, j);
        } else {
            print_lcs(i, j - 1);
        }
    }

    void print_solution() {
        cout << "Longest Common Subsequence:\n";
        print_lcs(m, n);
        cout << "\n\n";
        cout << "Entries in array c:\n";
        print_table(c, 0, m, 0, n, true);
        cout << '\n';
        cout << "Entries in array b:\n";
        print_table(b, 1, m, 1, n, true);
        cout << '\n';
        cout << "Solution: " << c[m][n] << endl;
    }
};

int main() {
    /* Textbook example. */
    string X = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
    string Y = {'B', 'D', 'C', 'A', 'B', 'A'};
    int m = X.length();
    int n = Y.length();

    auto solution = LCS_Length(X, Y, m, n);
    solution.print_solution(); // should be BCBA
}