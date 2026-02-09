#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool validPalindrome(string s){
        int left = 0;
        int right = s.size() - 1;
        while(left < right){
            if(s[left] != s[right]){
                return (isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1));
            }
            left++;
            right--;
        }
        return true;
    }
    bool isPalindrome(string s, int left, int right){
        cout << "Checking substring: " << s.substr(left, right-left+1) << endl;
        while(left < right){
            if(s[left] != s[right]){
                return false;
            }
            left++;   // BUG FIX: This was missing!
            right--;  // BUG FIX: This was missing!
        }
        return true;
    }
};

int main() {
    Solution sol;

    // Test cases with expected results
    vector<pair<string, bool>> testCases = {
        // Already palindromes (no deletion needed)
        {"aba", true},
        {"abba", true},
        {"a", true},
        {"aa", true},

        // Valid after deleting one character
        {"abca", true},      // Delete 'c' -> "aba"
        {"abcba", true},     // Already palindrome or delete middle
        {"deeee", true},     // Delete first 'd' -> "eeee"
        {"eeeed", true},     // Delete last 'd' -> "eeee"
        {"racecar", true},   // Already palindrome
        {"raceacar", true},  // Delete 'a' -> "racecar"

        // Delete from left side
        {"ebcbbececabbacecbbcbe", true},

        // Delete from right side
        {"abc", false},      // Cannot form palindrome by deleting one char
        {"abcdef", false},   // Cannot form palindrome

        // Edge cases
        {"", true},          // Empty string (palindrome)
        {"ab", true},        // Delete either 'a' or 'b' -> single char palindrome
        {"abb", true},       // Delete first 'a' -> "bb"
        {"bba", true},       // Delete last 'a' -> "bb"

        // Tricky cases
        {"aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga", true},
        {"abc", false},
        {"abcddcba", true},  // Already palindrome
        {"abcdedcba", true}, // Already palindrome
        {"abcdefdcba", true} // Cannot form palindrome by deleting one
    };

    int passed = 0;
    int failed = 0;

    cout << "Running test cases...\n" << endl;

    for (const auto& test : testCases) {
        string input = test.first;
        bool expected = test.second;
        bool result = sol.validPalindrome(input);

        if (result == expected) {
            cout << "PASS: \"" << input << "\" -> " << (result ? "true" : "false") << endl;
            passed++;
        } else {
            cout << "FAIL: \"" << input << "\" -> expected " << (expected ? "true" : "false")
                 << ", got " << (result ? "true" : "false") << endl;
            failed++;
        }
    }

    cout << "\n========================================" << endl;
    cout << "Total: " << testCases.size() << " tests" << endl;
    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "========================================" << endl;

    return 0;
}