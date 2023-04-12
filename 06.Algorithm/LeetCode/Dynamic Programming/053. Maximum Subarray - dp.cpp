#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int> &nums) {
        /* dp[i] = maximum subarray sum, but restricts that nums[i] is the right endpoint of the subarray. */
        vector<int> dp(nums.size());

        dp[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (dp[i - 1] >= 0) {
                dp[i] = dp[i - 1] + nums[i];
            } else {
                dp[i] = nums[i];
            }
        }

        /* Iterate through the dp array to obtain the final solution. */
        int result = dp[0];
        for (int i = 1; i < nums.size(); i++) {
            result = max(result, dp[i]);
        }

        return result;
    }
};