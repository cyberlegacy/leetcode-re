// STEP 1: Always put headers and 'using' statements at the VERY TOP.
// The compiler needs to know what 'vector', 'cout', 'size_t' etc. are before you use them.
#include <iostream> 
#include <vector>   
using namespace std;

// STEP 2: Now that the compiler knows what 'vector' is, you can define your class.
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        size_t length = flowerbed.size();
        int count = 0;
        for(size_t i = 0; i < length; i++) {
            if(flowerbed[i] == 0 && (i == 0 || flowerbed[i-1] == 0) && (i == length-1 || flowerbed[i+1] == 0)) {
                // This is your original logic. It has a small bug.
                // A better approach is to jump ahead after planting.
                flowerbed[i] = 1;
                count++;
            }
        }
        return count >= n;
    }
};

// STEP 3: Your main function comes last.
int main() {
    Solution sol;
    vector<int> a1{1,0,0,0,1};
    vector<int> a2{1,0,0,0,1};
    vector<int> a3{0,0,1,0,1};
    vector<int> a4{0};
    vector<int> a5{0,0};
    vector<int> a6{1,0,0,0,0,1};

    cout << boolalpha; // Prints true/false instead of 1/0 for better readability
    cout << sol.canPlaceFlowers(a1, 1) << "\n"; // 1
    cout << sol.canPlaceFlowers(a2, 2) << "\n"; // 0
    cout << sol.canPlaceFlowers(a3, 1) << "\n"; // 1
    cout << sol.canPlaceFlowers(a4, 1) << "\n"; // 1
    cout << sol.canPlaceFlowers(a5, 2) << "\n"; // 0
    cout << sol.canPlaceFlowers(a6, 1) << "\n"; // 1

    return 0;
}