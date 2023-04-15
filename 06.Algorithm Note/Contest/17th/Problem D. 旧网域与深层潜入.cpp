#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    string A, B;
    cin >> n >> A >> B;

    bool select_A = true;
    for (int i = 0; i < n; i++) {
        if (A[i] == B[i]) {
            char c = A[i];
            char invert = (c == '0') ? '1' : '0';
            cout << invert;
        } else {
            if (select_A) {
                cout << A[i];
                select_A = false;
            } else {
                cout << B[i];
                select_A = true;
            }
        }
    }
    cout << endl;

    return 0;
}