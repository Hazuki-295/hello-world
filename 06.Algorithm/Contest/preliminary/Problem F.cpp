#include <bits/stdc++.h>

using namespace std;

vector<int> construct_path(int color, vector<int> &chessboard, unordered_map<int, vector<size_t>> &link, int n) {
    vector<int> path;
    size_t index = 1;
    while (index <= n) {
        path.push_back(chessboard[index]);
        int current_color = chessboard[index];
        if (current_color == color) { // same color
            /* must be found, since it is on the chessboard */
            auto pos = find(link[color].begin(), link[color].end(), index);
            if (pos != link[color].end() - 1) { // not the last same color, move to next same color
                index = *(pos + 1);
            } else {
                index++; // the last same color
            }
        } else { // not the same color, just forward
            index++;
        }
    }
    return path;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> chessboard_A(n + 1);
    unordered_map<int, vector<size_t>> link_A; // <int color, vector<size_t> indexes>
    for (size_t i = 1; i <= n; i++) {
        scanf("%d", &chessboard_A[i]);
        link_A[chessboard_A[i]].push_back(i); // same color link
    }

    vector<int> chessboard_B(n + 1);
    unordered_map<int, vector<size_t>> link_B;
    for (size_t i = 1; i <= n; i++) {
        scanf("%d", &chessboard_B[i]);
        link_B[chessboard_B[i]].push_back(i);
    }

    int result = 0;
    for (int color = 1; color <= m; color++) {
        vector<int> path_A = construct_path(color, chessboard_A, link_A, n);
        vector<int> path_B = construct_path(color, chessboard_B, link_B, n);
        if (path_A == path_B) {
            result++;
        }
    }

    printf("%d\n", result);

    return 0;
}