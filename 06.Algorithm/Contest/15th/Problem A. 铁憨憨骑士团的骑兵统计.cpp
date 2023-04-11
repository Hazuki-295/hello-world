#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    int dbThreshold = 70;
    int count = 0, db;
    while (n--) {
        scanf("%d", &db);
        if (db > dbThreshold) {
            count++;
        }
    }
    printf("%d", count);
    return 0;
}