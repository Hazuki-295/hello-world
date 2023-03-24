#include <vector>

using namespace std;

class NumArray {
public:
    vector<int> prefixSums; // prefixSums[i + 1] = nums[0] + nums[1] + ... + nums[i], prefixSums[0] = 0

    NumArray(vector<int> &nums) {
        int n = nums.size();
        prefixSums.resize(n + 1);
        /* preprocessing, calculating prefix sums */
        for (int i = 0; i < n; i++) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return prefixSums[right + 1] - prefixSums[left]; // sum of right - left + 1 numbers
    }
};