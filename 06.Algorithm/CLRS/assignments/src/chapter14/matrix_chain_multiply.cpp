#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

template<typename T>
void print_table(vector<vector<T>> &vec, int start_i, int end_i, int start_j, int end_j, bool whole_table = false) {
    /* Calculate the maximum width of any element in the vector of vectors */
    int max_width = 0;
    for (int i = start_i; i <= end_i; i++) {
        for (int j = whole_table ? start_j : start_j + i - start_i; j <= end_j; j++) {
            stringstream ss;
            ss << vec[i][j];
            int width = ss.str().length();
            if (width > max_width) {
                max_width = width;
            }
        }
    }

    /* Output each element in the vector of vectors with the same width */
    for (int i = start_i; i <= end_i; i++) {
        if (!whole_table) {
            for (int j = start_j; j < start_j + i - start_i; j++) {
                cout << string(max_width, ' ') << ' ';
            }
        }
        for (int j = whole_table ? start_j : start_j + i - start_i; j <= end_j; j++) {
            cout << std::setw(max_width) << vec[i][j] << " ";
        }
        cout << endl;
    }
}

/* Determine the optimal number of scalar multiplications needed to compute the matrix chain product A[1] * A[2] * ... * A[n]. */
class Matrix_Chain_Order {
private:
    vector<vector<int>> m; // array with m[i, j] as the lowest number of scalar multiplications to compute A(i..j).
    vector<vector<int>> s; // array that records which position to split an optimal solution to a sub-problem of m[i, j].

public:
    Matrix_Chain_Order(vector<int> &p, int n) {
        m = vector<vector<int>>(n + 1, vector<int>(n + 1)); // using indices m[1:n, 1:n], i <= j
        s = vector<vector<int>>(n + 1, vector<int>(n + 1)); // using indices s[1:n-1, 2:n], i < j

        for (int i = 1; i <= n; i++) { // chain length 1 (not necessary in C++)
            m[i][i] = 0;
        }

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
            print_optimal_parens(i, s[i][j]);     // left  side, A(i...k)
            print_optimal_parens(s[i][j] + 1, j); // right side, A(k+1...j)
            printf(")");
        }
    }

    void print_solution(int n) {
        cout << "Optimal Parenthesization:\n";
        print_optimal_parens(1, n);
        cout << "\n\n";
        cout << "Entries in array m:\n";
        print_table(m, 1, n, 1, n);
        cout << '\n';
        cout << "Entries in array s:\n";
        print_table(s, 1, n - 1, 2, n);
        cout << '\n';
        cout << "Solution: " << m[1][n] << endl;
    }
};


int main() {
    /* Matrix chain multiply example from textbook. */
    vector<int> dimensions = {30, 35, 15, 5, 10, 20, 25};
    int n = dimensions.size() - 1;
    auto solution = Matrix_Chain_Order(dimensions, n);
    solution.print_solution(n);

    return 0;
}