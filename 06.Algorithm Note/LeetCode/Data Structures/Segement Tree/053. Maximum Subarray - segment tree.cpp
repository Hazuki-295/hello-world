#include <vector>

using namespace std;

class Solution {
public:
    /* For the array interval [left, right], maintain the following information. */
    struct Status {
        int leftSum;  // Maximum subarray sum, but restricts that a[left] is the left endpoint of the subarray.
        int rightSum; // Similarly, maximum subarray sum with the restriction that a[right] is the right endpoint.
        int maxSum;   // Maximum subarray sum of the whole interval.
        int intervalSum;
    };

    /* Merge two segments. */
    Status pushUp(Status left, Status right) {
        int intervalSum = left.intervalSum + right.intervalSum;

        /* Since interval must be continuous, these two choice cover all circumstances. */
        int leftSum = max(left.leftSum, left.intervalSum + right.leftSum);
        int rightSum = max(right.rightSum, right.intervalSum + left.rightSum);

        /* Likewise, the result interval may across the middle point, or just stay in one side. */
        int maxSum = max(max(left.maxSum, right.maxSum), left.rightSum + right.leftSum);

        return (Status) {leftSum, rightSum, maxSum, intervalSum};
    };

    Status query(vector<int> &array, int left, int right) {
        if (left == right) {
            return (Status) {array[left], array[left], array[left], array[left]};
        }
        int middle = (left + right) >> 1;
        Status leftSub = query(array, left, middle);
        Status rightSub = query(array, middle + 1, right);
        return pushUp(leftSub, rightSub);
    }

    int maxSubArray(vector<int> &nums) {
        return query(nums, 0, nums.size() - 1).maxSum;
    }
};