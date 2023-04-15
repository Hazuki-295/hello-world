#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        size_t n, m, x, y, hp;
        cin >> n >> m >> x >> y >> hp;

        size_t min_cost = numeric_limits<size_t>::max();
        for (size_t num_of_n = 1; num_of_n <= n; num_of_n++) {
            for (size_t num_of_m = 0; num_of_m <= m; num_of_m++) {
                size_t hurt = num_of_n * (num_of_m + 1);
                if (hurt >= hp) {
                    size_t cost = num_of_n * x + num_of_m * y;
                    min_cost = min(cost, min_cost);
                    break;
                }
            }
        }

        if (min_cost != numeric_limits<size_t>::max()) {
            cout << min_cost << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}