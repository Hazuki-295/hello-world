#include <bits/stdc++.h>

int main() {
    int x1, y1; // A
    int x2, y2; // B
    int x3, y3; // C

    scanf("%d%d", &x1, &y1);
    scanf("%d%d", &x2, &y2);
    scanf("%d%d", &x3, &y3);

    size_t distance_AB = pow(x1 - x2, 2) + pow(y1 - y2, 2);
    size_t distance_AC = pow(x1 - x3, 2) + pow(y1 - y3, 2);
    size_t distance_CB = pow(x3 - x2, 2) + pow(y3 - y2, 2);

    if (distance_AB >= distance_AC + distance_CB) {
        printf("Longlive Friendship!\n");
    } else {
        printf("Rush B!\n");
    }

    return 0;
}