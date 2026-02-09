#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary){
        string result = "";

        for(auto &word : dictionary){
            if(isSubsequence(s, word)){
                // Update if longer, OR same length but lexicographically smaller
                if(word.size() > result.size() ||
                   (word.size() == result.size() && word < result)){
                    result = word;
                }
            }
        }
        return result;
    }
    bool isSubsequence(string s, string word){
        size_t i = 0;
        size_t j = 0;
        while(i < s.size() && j < word.size()){
            if(s[i] == word[j]){
                j++;
            }
            i++;
        }
        return j == word.size();
    }
};

int main(){
    Solution sol;

    // Test cases: (s, dictionary, expected)
    struct TestCase {
        string s;
        vector<string> dictionary;
        string expected;
        string description;
    };

    vector<TestCase> testCases = {
        // Basic case from problem
        {"abpcplea", {"ale","apple","monkey","plea"}, "apple", "Basic example"},

        // Same length words - lexicographical order matters
        {"abpcplea", {"ale", "ape", "abc"}, "abc", "Same length: choose lexicographically smallest"},
        {"abpcplea", {"plea", "apple"}, "apple", "Longer word wins"},

        // No valid subsequence
        {"abpcplea", {"xyz", "monkey"}, "", "No valid subsequence"},

        // Empty dictionary
        {"abpcplea", {}, "", "Empty dictionary"},

        // Single character
        {"a", {"a", "b", "c"}, "a", "Single character match"},
        {"abc", {"a", "b", "c"}, "a", "Multiple single chars, pick first lexicographically"},

        // All words same length
        {"abcde", {"ace", "acd", "ade", "bde"}, "acd", "Same length: lexicographical order"},
        {"abcde", {"zzz", "aaa", "ace"}, "ace", "Same length: 'ace' is valid and smallest"},

        // Longer word appears later in dictionary
        {"abpcplea", {"ale", "apple"}, "apple", "Longer word comes second"},
        {"abpcplea", {"apple", "ale"}, "apple", "Longer word comes first"},

        // Multiple valid words of same max length
        {"abcdefg", {"abef", "abcf"}, "abcf", "Same length, choose smaller"},

        // Edge case: empty string s
        {"", {"a", "b"}, "", "Empty string s"},
        {"", {""}, "", "Both empty"},

        // Complex subsequences
        {"aewbcnpoiu", {"apple", "ewcn", "ahbgdc", "npui"}, "ewcn", "Complex subsequence check"},

        // All characters same
        {"aaaa", {"aa", "aaa", "a", "aaaa"}, "aaaa", "Repeated characters - longest"},

        // Dictionary has duplicates
        {"abc", {"ac", "ab", "ac"}, "ab", "Duplicates in dictionary"},

        // Very long valid word
        {"abcdefghijklmnop", {"ap", "abcdefghijklmnop", "aceg"}, "abcdefghijklmnop", "Exact match (longest)"},

        // Ties with different lengths
        {"abcde", {"ace", "ad", "ab"}, "ace", "Choose longest among valid"},
    };

    int passed = 0;
    int failed = 0;

    cout << "Running test cases...\n" << endl;

    for (size_t i = 0; i < testCases.size(); i++) {
        auto& test = testCases[i];
        string result = sol.findLongestWord(test.s, test.dictionary);

        if (result == test.expected) {
            cout << "PASS [" << i+1 << "]: " << test.description << endl;
            cout << "       s=\"" << test.s << "\", result=\"" << result << "\"" << endl;
            passed++;
        } else {
            cout << "FAIL [" << i+1 << "]: " << test.description << endl;
            cout << "       s=\"" << test.s << "\"" << endl;
            cout << "       Expected: \"" << test.expected << "\"" << endl;
            cout << "       Got:      \"" << result << "\"" << endl;
            failed++;
        }
        cout << endl;
    }

    cout << "========================================" << endl;
    cout << "Total: " << testCases.size() << " tests" << endl;
    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "========================================" << endl;

    return 0;
}