#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> rotate(const vector<vector<char>> &mask, int n) {
    vector<vector<char>> result(mask);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = mask[n - 1 - j][i];
        }
    }
    return result;
}

vector<vector<char>> mirror(const vector<vector<char>> &mask, int n) {
    vector<vector<char>> result(mask);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = mask[i][n - 1 - j];
        }
    }
    return result;
}

int main() {
    int n, query;
    cin >> n >> query;
    vector<vector<char>> mask(n, vector<char>(n));
    vector<vector<char>> message(n, vector<char>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mask[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> message[i][j];
        }
    }

    vector<vector<char>> current = mask;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (current[i][j] == 'O') {
                cout << message[i][j];
            }
        }
    }

    while (query--) {
        int op;
        cin >> op;
        switch (op) {
            case 1:
                current = rotate(current, n); // 90
                break;
            case 2:
                current = rotate(current, n); // 180
                current = rotate(current, n); // 180
                break;
            case 3:
                current = rotate(current, n); // 270
                current = rotate(current, n); // 270
                current = rotate(current, n); // 270
                break;
            case 4:
                current = mirror(current, n);
                break;
            case 5:
                break;
            default:
                assert(false);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (current[i][j] == 'O') {
                    cout << message[i][j];
                }
            }
        }
    }
    cout << endl;

    return 0;
}