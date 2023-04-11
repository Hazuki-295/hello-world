#include <bits/stdc++.h>

using namespace std;

int main() {
    int t, n;
    scanf("%d%d", &t, &n);

    int start_time[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &start_time[i]);
    }

    while (t--) {
        int stop_time, arrive, max;
        scanf("%d%d%d", &stop_time, &arrive, &max);

        /* num of lanes，use binary search. */
        int left = 1;
        int right = n;
        int solution = 0; // default no solution
        while (left <= right) {
            int middle = (left + right) >> 1;
            size_t waiting_car = (stop_time + start_time[middle]) * (size_t) arrive;
            size_t max_capacity = middle * (size_t) max;
            if (waiting_car <= max_capacity) { // wide enough
                solution = middle;
                right = middle - 1;
            } else { // too narrow
                left = middle + 1;
            }
        }
        if (solution) {
            printf("%d\n", solution);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}