#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    string p;
    cin >> n >> p;

    int last_num = p[p.length() - 1] - '0';

    vector<int> pow_of_last_num(n);
    pow_of_last_num[0] = 1;
    for (int i = 1; i < n; i++) {
        pow_of_last_num[i] = pow_of_last_num[i - 1] * last_num;
    }

    int result = 0;
    while ((--n) >= 0) {
        string number;
        cin >> number;
        int last_num_of_num = number[number.length() - 1] - '0';
        result += last_num_of_num * pow_of_last_num[n];
    }

    if (result % 2 == 0) {
        printf("even\n");
    } else {
        printf("odd\n");
    }

    return 0;
}