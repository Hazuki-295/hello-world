#include <iostream>
#include <vector>
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