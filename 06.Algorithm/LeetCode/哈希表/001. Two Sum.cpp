#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> hashtable; // <value, index of num>
        for (int i = 0; i < nums.size(); i++) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) { // found the target
                return {it->second, i};  // return two indexes
            } else {
                hashtable[nums[i]] = i; // not found, add to the hashtable for subsequent lookup
            }
        }
        return {};
    }
};