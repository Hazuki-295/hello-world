#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> tokens;
    while (n--) {
        string token;
        cin >> token;
        tokens.push_back(token);
    }

    string message;
    cin >> message;
    vector<bool> mask(message.size(), false);

    /* mask or not? */
    for (const auto &token: tokens) {
        int begin_index, end_index;
        for (begin_index = 0; (end_index = begin_index + token.length()) <= message.length(); begin_index++) {
            string sub = message.substr(begin_index, token.size());
            if (sub == token) {
                replace(mask.begin() + begin_index, mask.begin() + end_index, false, true);
            }
        }
    }

    /* output the masked message */
    for (int i = 0; i < message.size(); i++) {
        if (!mask[i]) {
            cout << message[i];
        } else {
            cout << "**";
            while (mask[++i]);
            i--;
        }
    }

    return 0;
}