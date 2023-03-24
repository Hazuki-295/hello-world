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
            // prefixSums[i] = prefixSums[i - 1] + nums[i] (for array index 1:n)
        }
    }

    int sumRange(int left, int right) {
        return prefixSums[right + 1] - prefixSums[left];
        // prefixSums[right] - prefixSums[left - 1] (for array index 1:n)
    }
};