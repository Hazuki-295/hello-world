#include <iostream>
#include <vector>
#include <limits>

using namespace std;

/* Determine the optimal number of scalar multiplications needed
 * to compute the matrix chain product A[1] * A[2] * ... * A[n]. */
class Matrix_Chain_Order {
private:
    vector<vector<int>> m; // array with m[i, j] as the lowest number of scalar multiplications to compute A(i..j).
    vector<vector<int>> s; // array that records which position to split an optimal solution to a sub-problem of m[i, j].
public:
    Matrix_Chain_Order(vector<int> &p, int n) {
        m = vector<vector<int>>(n + 1, vector<int>(n + 1)); // using indices m[1:n+1, 1:n+1]
        s = vector<vector<int>>(n + 1, vector<int>(n + 1)); // using indices s[1:n, 2:n+1]

        for (int length = 2; length <= n; length++) {   // l is the chain length
            for (int i = 1; i <= n - length + 1; i++) { // chain begins at A[i]
                int j = i + length - 1;                 // chain ends at A[j]
                m[i][j] = numeric_limits<int>::max();
                for (int k = i; k < j; k++) { // try splitting between A[k] and A[k+1] (i <= k < j)
                    int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                    if (q < m[i][j]) {
                        m[i][j] = q; // remember this cost
                        s[i][j] = k; // remember this index
                    }
                }
            }
        }
    }

    /* Print an optimal parenthesization of the matrix chain from A[i] to A[j]. */
    void print_optimal_parens(int i, int j) {
        if (i == j) {
            printf("A[%d]", i);
        } else {
            printf("(");
            print_optimal_parens(i, s[i][j]);     // left side, A(i:k)
            print_optimal_parens(s[i][j] + 1, j); // right side, A(k+1:j)
            printf(")");
        }
    }
};


int main() {
    /* Matrix chain multiply example from textbook. */
    vector<int> dimensions = {30, 35, 15, 5, 10, 20, 25};
    int n = dimensions.size() - 1;

    auto solution = Matrix_Chain_Order(dimensions, n);
    solution.print_optimal_parens(1, n); // should print ((A[1](A[2]A[3]))((A[4]A[5])A[6]))
    cout << endl;

    return 0;
}