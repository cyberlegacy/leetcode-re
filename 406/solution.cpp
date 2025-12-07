#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // Sort by height descending, then by k ascending
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] > b[0];  // Taller first
            return a[1] < b[1];                     // Same height: smaller k first
        });

        vector<vector<int>> result;
        for (const auto& person : people) {
            // Insert person at index k
            result.insert(result.begin() + person[1], person);
        }

        return result;
    }
};
