#include <vector>

using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>> &bookings, int n) {
        vector<int> flights(n + 1);
        vector<int> diff(n + 2); // difference array

        /* Each time operates on an entire interval of the array. */
        for (auto booking: bookings) {
            int first = booking[0];
            int last = booking[1];
            int seats = booking[2];

            diff[first] += seats;
            diff[last + 1] -= seats;
        }
        /* Preforming prefix sum gives the flight array. */
        for (int i = 1; i <= n; i++) {
            flights[i] = flights[i - 1] + diff[i];
        }
        flights.erase(flights.begin());
        return flights;
    }
};