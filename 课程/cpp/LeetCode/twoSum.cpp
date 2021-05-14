#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return { it->second, i };
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};

int main()
{
    vector<int> temp = { 2,7,11,15 }; int target = 9;
    Solution solve;
    vector<int> result = solve.twoSum(temp, target);
    for (auto x : result)
    {
        cout << x << ' ';
    }

    return 0;
}