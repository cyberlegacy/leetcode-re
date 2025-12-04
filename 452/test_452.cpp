#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int count = 1;
        int end = points[0][1];
        for(int i = 1; i < points.size(); i++) {
            if(points[i][0] > end) {
                count++;
                end = points[i][1];
            }
        }
        return count;
    }
};

void test(vector<vector<int>> points, int expected) {
    Solution sol;
    int result = sol.findMinArrowShots(points);
    cout << "Input: [";
    for(int i = 0; i < points.size(); i++) {
        cout << "[" << points[i][0] << "," << points[i][1] << "]";
        if(i < points.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "Expected: " << expected << ", Got: " << result;
    if(result == expected) {
        cout << " ✓ PASS" << endl;
    } else {
        cout << " ✗ FAIL" << endl;
    }
    cout << endl;
}

int main() {
    cout << "=== Testing Minimum Number of Arrows to Burst Balloons ===" << endl << endl;
    
    // Test 1: Basic overlapping balloons
    test({{10,16},{2,8},{1,6},{7,12}}, 2);
    
    // Test 2: All balloons overlap at one point
    test({{1,2},{2,3},{3,4},{4,5}}, 2);
    
    // Test 3: No overlapping balloons
    test({{1,2},{3,4},{5,6},{7,8}}, 4);
    
    // Test 4: All balloons completely overlap
    test({{1,10},{2,9},{3,8},{4,7}}, 1);
    
    // Test 5: Single balloon
    test({{1,5}}, 1);
    
    // Test 6: Two overlapping balloons
    test({{1,5},{3,7}}, 1);
    
    // Test 7: Two non-overlapping balloons
    test({{1,2},{3,4}}, 2);
    
    // Test 8: Complex case with multiple groups
    test({{1,6},{2,8},{7,12},{10,16},{15,20},{18,22}}, 3);
    
    // Test 9: Edge case with negative numbers
    test({{-10,-5},{-8,-2},{-6,-1},{0,5}}, 2);
    
    // Test 10: Large numbers (INT_MAX edge case)
    test({{-2147483648,2147483647},{-2147483647,2147483646}}, 1);
    
    return 0;
}

