#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        long left = 0;
        long right = sqrt(c);
        while(left <= right) {
            long sum = left * left + right * right;
            if(sum < c) {
                left++;
            }
            else if(sum > c) {
                right--;
            }
            else {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Solution sol;

    // Test cases with expected results
    vector<pair<int, bool>> testCases = {
        {0, true},      // 0^2 + 0^2 = 0
        {1, true},      // 0^2 + 1^2 = 1
        {2, true},      // 1^2 + 1^2 = 2
        {3, false},     // No valid combination
        {4, true},      // 0^2 + 2^2 = 4
        {5, true},      // 1^2 + 2^2 = 5
        {6, false},     // No valid combination
        {7, false},     // No valid combination
        {8, true},      // 2^2 + 2^2 = 8
        {13, true},     // 2^2 + 3^2 = 13
        {25, true},     // 3^2 + 4^2 = 25 or 0^2 + 5^2 = 25
        {100, true},    // 0^2 + 10^2 = 100 or 6^2 + 8^2 = 100
        {1000, true},   // 10^2 + 30^2 = 1000
        {999, false},   // No valid combination
        {2147483647, false}  // Max int test
    };

    int passed = 0;
    int failed = 0;

    cout << "Running test cases...\n" << endl;

    for (const auto& test : testCases) {
        int input = test.first;
        bool expected = test.second;
        bool result = sol.judgeSquareSum(input);

        if (result == expected) {
            cout << "PASS: c = " << input << ", result = " << (result ? "true" : "false") << endl;
            passed++;
        } else {
            cout << "FAIL: c = " << input << ", expected = " << (expected ? "true" : "false")
                 << ", got = " << (result ? "true" : "false") << endl;
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