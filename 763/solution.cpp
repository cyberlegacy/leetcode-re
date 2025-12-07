#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        // Store the last occurrence index of each character
        int lastIndex[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            lastIndex[s[i] - 'a'] = i;
        }

        vector<int> result;
        int start = 0;  // Start of current partition
        int end = 0;    // End of current partition (farthest we must go)

        for (int i = 0; i < s.size(); i++) {
            // Extend the partition to include the last occurrence of current char
            end = max(end, lastIndex[s[i] - 'a']);

            // If we've reached the end of current partition
            if (i == end) {
                result.push_back(end - start + 1);
                start = i + 1;
            }
        }

        return result;
    }
};
