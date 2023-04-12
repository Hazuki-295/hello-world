#include <vector>

using namespace std;

class NumArray {
public:
    vector<int> prefixSum; // prefixSum[i + 1] = nums[0] + nums[1] + ... + nums[i], prefixSum[0] = 0

    NumArray(vector<int> &nums) {
        int n = nums.size();
        prefixSum.resize(n + 1);
        /* preprocessing, calculating prefix sum */
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
            // prefixSum[i] = prefixSum[i - 1] + nums[i] (for array index 1:n)
        }
    }

    int sumRange(int left, int right) {
        return prefixSum[right + 1] - prefixSum[left];
        // prefixSum[right] - prefixSum[left - 1] (for array index 1:n)
    }
};