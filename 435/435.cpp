#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // --- CHANGE 1 ---
        // Use size_t, which is the proper unsigned type for container sizes.
        // This prevents a warning when comparing an 'int' with the result of '.size()'.
        const size_t numIntervals = intervals.size();
        
        if (numIntervals <= 1) {
            return 0;
        }

        // Sort by the end point of the intervals. This is the core of the greedy strategy.
        // If end points are the same, sorting by start point is a good practice for stability.
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[1] == b[1]) return a[0] < b[0];
            return a[1] < b[1];
        });

        int countNonOverlapping = 1; // Always take the first interval after sorting.
        int lastEnd = intervals[0][1];

        // --- CHANGE 2 ---
        // The loop counter 'i' is declared as size_t.
        // This is crucial because it's used as an index for 'intervals[i]'.
        // A vector's index operator expects an unsigned type like size_t.
        // Using 'int i' here would cause the -Wsign-conversion warning.
        for (size_t i = 1; i < numIntervals; ++i) {
            // If the start of the current interval is not before the end of the last selected one,
            // it means they do not overlap, so we can select it.
            if (intervals[i][0] >= lastEnd) {
                ++countNonOverlapping;
                lastEnd = intervals[i][1];
            }
        }
        
        // --- CHANGE 3 ---
        // The function must return an 'int'. Since 'numIntervals' is size_t,
        // we must explicitly and safely cast the final result back to 'int'.
        return static_cast<int>(numIntervals) - countNonOverlapping;
    }
};

// The main function for testing remains the same.
int main() {
    Solution solution;

    vector<vector<int>> test1{{1,2},{2,3},{3,4},{1,3}}; // expected 1
    cout << "Test 1: " << solution.eraseOverlapIntervals(test1) << "\n";

    vector<vector<int>> test2{{1,2},{1,2},{1,2}};      // expected 2
    cout << "Test 2: " << solution.eraseOverlapIntervals(test2) << "\n";
    
    vector<vector<int>> test3{{1,2},{2,3}};            // expected 0
    cout << "Test 3: " << solution.eraseOverlapIntervals(test3) << "\n";

    return 0;
}

