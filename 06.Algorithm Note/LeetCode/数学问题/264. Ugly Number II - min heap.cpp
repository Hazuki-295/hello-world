#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> factors = {2, 3, 5};
        unordered_set<long> seen; // use a hashtable to avoid duplicate elements
        priority_queue<long, vector<long>, greater<long>> heap; // min heap, the root node is always smallest

        heap.push(1L); // first ugly number 1
        int uglyNumber = 0;
        for (int i = 0; i < n; i++) {
            long current = heap.top(); // smallest ugly number in the heap
            heap.pop(); // each loop pop exactly one ugly number
            uglyNumber = current; // pop n times in all, finally it will be the answer of nth ugly number

            for (int factor: factors) {
                long next = current * factor;
                if (!seen.count(next)) { // never seen before
                    seen.insert(next);
                    heap.push(next);
                }
            }
        }
        return uglyNumber;
    }
};