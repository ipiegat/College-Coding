/*Instructions-
Write the function splitIntervals which takes an vector of integer pairs "intervals"
	and a vector of integers "vals_to_remove"
Each pair element in intervals represents an integer interval, from [pair.first] to [pair.second]
When this function is called, all integers in vals_to_remove should no longer be included in any of the intervals
For example, if intervals equals {{1,8},{7,12}} and vals_to_remove equals {3,5},
after the function is called, intervals will be equal to {{1,2},{4,4},{6,8},{7,12}}.
Note that now, neither 3 nor 5 are present in any of these intervals.
Also, for testing purpose, the order of the intervals in the vector does not matter.
*/
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void splitIntervals(vector<pair<int, int>> &intervals, const vector<int> &vals_to_remove) {
    vector<pair<int, int>> new_intervals;
    vector<int> sorted_vals = vals_to_remove;

    sort(sorted_vals.begin(), sorted_vals.end());

    for (auto interval : intervals) {
        int start = interval.first;
        int end = interval.second;

        for (int val : sorted_vals) {
            if (val < start || val > end) continue;

            if (val == start) {
                start++;
            } else if (val == end) {
                end--;
            } else {
                new_intervals.push_back({start, val - 1});
                start = val + 1;
            }
        }

        if (start <= end) {
            new_intervals.push_back({start, end});
        }
    }

    intervals = new_intervals;
}
