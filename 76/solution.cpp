#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        // need: stores how many of each char we need from t
        // window: stores how many of each char we currently have in our window
        unordered_map<char, int> need, window;

        // count every character in t, e.g. t="ABC" -> need={A:1, B:1, C:1}
        for (char c : t) need[c]++;

        // left/right are the two boundaries of our sliding window [left, right)
        int left = 0, right = 0;

        // valid counts how many distinct chars in need have been fully satisfied
        // e.g. if need={A:1,B:1,C:1} and window has A:1,B:1 then valid=2
        int valid = 0;

        // start = beginning index of the best answer so far
        // len = length of the best answer so far (INT_MAX means no answer yet)
        int start = 0, len = INT_MAX;

        // outer loop: expand the window by moving right forward one step at a time
        while (right < (int)s.size()) {
            // c is the character we are adding into the window
            char c = s[right];
            // move right boundary forward (the window now includes this char)
            right++;

            // only care about this char if it's one we need (exists in t)
            if (need.count(c)) {
                // increase this char's count in our window
                window[c]++;
                // if this char's count now exactly matches what we need,
                // one more distinct char is fully satisfied
                if (window[c] == need[c])
                    valid++;
            }

            // inner loop: when ALL chars are satisfied, try to shrink from the left
            // to find a smaller valid window
            // valid == need.size() means every distinct char in t is satisfied
            while (valid == (int)need.size()) {
                // current window [left, right) is valid — check if it's the smallest
                if (right - left < len) {
                    start = left;       // record where this window starts
                    len = right - left;  // record its length
                }

                // d is the character we are about to remove from the window
                char d = s[left];
                // move left boundary forward (shrink the window)
                left++;

                // only care if this char is one we need
                if (need.count(d)) {
                    // if removing this char will break the requirement
                    // (count drops below needed), one fewer char is satisfied
                    if (window[d] == need[d])
                        valid--;
                    // actually remove it from window count
                    window[d]--;
                }
            }
            // after shrinking, the window is no longer valid,
            // so we go back to the outer loop to expand right again
        }

        // if len was never updated, no valid window exists -> return ""
        // otherwise return the substring starting at 'start' with length 'len'
        return len == INT_MAX ? "" : s.substr(start, len);
    }
};
