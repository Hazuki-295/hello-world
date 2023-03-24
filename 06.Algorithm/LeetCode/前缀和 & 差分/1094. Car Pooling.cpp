#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool carPooling(vector<vector<int>> &trips, int capacity) {
        int maxDistance = 1e3 + 1;
        vector<int> overhead(maxDistance + 1); // overhead of the car at distance[i], initial all 0
        vector<int> diff(maxDistance + 1);     // difference array of overhead

        for (auto trip: trips) {
            int numPassenger = trip[0];
            int from = trip[1] + 1;
            int to = trip[2] + 1;
            diff[from] += numPassenger; // passengers get on
            diff[to] -= numPassenger;   // passengers get off
        }

        /* The prefix sum of diff array gives the overhead array. */
        for (int i = 1; i <= maxDistance; i++) {
            overhead[i] = overhead[i - 1] + diff[i];
            if (overhead[i] > capacity) {
                return false;
            }
        }
        return true;
    }
};