#include <bits/stdc++.h>

using namespace std;

// Function to compute the prime factorization of a number
vector<int> prime_factors(int n) {
    vector<int> factors;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) factors.push_back(n); // prime number

    return factors;
}

vector<int> productList;

void generateProducts(vector<int> &nums, int startIndex, int currProduct) {
    if (startIndex == nums.size()) { // Base case: end of list
        productList.push_back(currProduct);
        return;
    }

    generateProducts(nums, startIndex + 1, currProduct * nums[startIndex]); // include current element
    generateProducts(nums, startIndex + 1, currProduct); // exclude current element
}

static vector<int> getAllProducts(vector<int> &nums) {
    productList.clear();

    generateProducts(nums, 0, 1); // start with index 0 and initial product of 1

    sort(productList.begin(), productList.end());
    productList.erase(unique(productList.begin(), productList.end()), productList.end());

    return productList;
}

int find_pairs(int x) {
    auto factors = prime_factors(x);
    vector<int> items = getAllProducts(factors);

    int result = 0;
    for (auto item: items) {
        auto factors_of_item = prime_factors(item);
        vector<int> products = getAllProducts(factors_of_item);
        result += products.size();
    }
    return result;
}

int main() {
    size_t scale = 10e3;
    size_t *seq = new size_t[scale];
    for (size_t i = 1; i < scale; i++) {
        seq[i] = find_pairs(i);
    }

    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        size_t n;
        cin >> n;
        size_t result = 0;
        for (size_t j = 1; j <= n; j++) {
            result += seq[j];
        }

        cout << result % 998244353 << '\n';
    }

    return 0;
}