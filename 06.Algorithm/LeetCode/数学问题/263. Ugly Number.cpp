#include <vector>

using namespace std;

class Solution {
public:
    bool isUgly(int n) {
        if (n <= 0) return false;

        vector<int> factors = {2, 3, 5};
        /* consider all possible factors of an ugly number */
        for (auto factor: factors) {
            while (n % factor == 0) {
                n /= factor;
            }
        }
        return n == 1; // n containing only the prime factors 2, 3, and 5
    }
};