#include <bits/stdc++.h>

using namespace std;

int main() {
    int row, col;
    scanf("%d%d", &row, &col);

    string line;
    getline(cin, line); // Empty line.

    vector<string> box;
    for (int i = 0; i < row; i++) {
        getline(cin, line);
        box.push_back(line);
    }

    int n;
    scanf("%d", &n);

    /* Input test cases. */
    vector<vector<string>> test_boxes;
    while (n--) {
        getline(cin, line); // Empty line.

        vector<string> test_box;
        for (int i = 0; i < row; i++) {
            getline(cin, line);
            test_box.push_back(line);
        }
        test_boxes.push_back(test_box);
    }

    int r;
    scanf("%d", &r);

    int count = 0;
    for (vector<string> test_box: test_boxes) {
        int diff = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                char x = box[i][j];
                char y = test_box[i][j];
                if (isalpha(x) && isalpha(y)) {
                    diff += abs(toupper(x) - toupper(y));
                } else {
                    diff += abs(x - y);
                }
            }
        }
        if (diff <= r) count++;
    }

    printf("%d", count);

    return 0;
}