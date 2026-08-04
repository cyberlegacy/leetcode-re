#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) return 0;

        unordered_map<char, int> frequency;
        int left = 0;
        int best = 0;

        for (int right = 0; right < static_cast<int>(s.size()); right++) {
            frequency[s[right]]++;

            // Remove characters from the left until at most k remain.
            while (static_cast<int>(frequency.size()) > k) {
                char outgoing = s[left++];
                if (--frequency[outgoing] == 0) {
                    frequency.erase(outgoing);
                }
            }

            best = max(best, right - left + 1);
        }

        return best;
    }
};
