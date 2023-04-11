#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, d;
    scanf("%d%d", &n, &d);

    int max_width = 360 - d;

    vector<int> cuts(n);
    for (int i = 0; i < cuts.size(); i++) {
        scanf("%d", &cuts[i]);
    }
    sort(cuts.begin(), cuts.end());

    cuts.push_back(cuts[0] + 360);

    for (int i = 1; i < cuts.size(); i++) {
        int width = cuts[i] - cuts[i - 1];
        if (width > max_width) {
            printf("NO");
            return 0;
        }
    }

    printf("YES");
    return 0;
}