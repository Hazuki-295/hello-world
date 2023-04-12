#include <bits/stdc++.h>

using namespace std;

int main() {
    string empty_line;
    getline(cin, empty_line); // Empty line.

    auto length = empty_line.length();

    string line2, line3;
    getline(cin, line2);
    getline(cin, line3);

    vector<int> digits;
    size_t index = 0;
    while (index < length) {
        if (line2[index] == '8') {
            size_t start = index;
            while (line2[++index] == '8');
            size_t end = index;

            if (line2.substr(start, end - start) == line3.substr(start, end - start)) {
                digits.push_back(1);
            } else {
                digits.push_back(0);
            }
        } else if (line2[index] == '0') {
            index++;
        }
    }

    int result = 0;
    for (size_t i = 0; i < digits.size(); i++) {
        result += digits[i] * (int) pow(2, digits.size() - 1 - i);
    }
    cout << result << endl;

    return 0;
}