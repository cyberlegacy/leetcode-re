# 680. Valid Palindrome II

## Problem
Given a string `s`, return `true` if the `s` can be palindrome after deleting **at most one** character from it.

## Approach

### Two-Pointer Technique with One Deletion Allowed

The algorithm uses a two-pointer approach with a helper function to check if a substring is a palindrome:

1. **Main function `validPalindrome(s)`:**
   - Initialize `left = 0` and `right = s.size() - 1`
   - While `left < right`:
     - If `s[left] == s[right]`, move both pointers inward (`left++`, `right--`)
     - If `s[left] != s[right]`, we found a mismatch:
       - Try deleting the left character: check if `isPalindrome(s, left+1, right)` is true
       - OR try deleting the right character: check if `isPalindrome(s, left, right-1)` is true
       - If either works, return `true`
   - If we finish the loop without mismatches, return `true` (already a palindrome)

2. **Helper function `isPalindrome(s, left, right)`:**
   - Check if the substring from `left` to `right` is a palindrome
   - Use two pointers, no deletion allowed
   - **Critical:** Must increment `left++` and decrement `right--` to avoid infinite loop

## Time Complexity
**O(n)** - In the worst case, we scan the string once in `validPalindrome`, and when a mismatch occurs, we check at most two substrings of length O(n) using `isPalindrome`.

## Space Complexity
**O(1)** - Only using a constant amount of extra space (pointers).

## Key Insights

### 1. Why Check Both Skip Options?
When we find a mismatch at `s[left] != s[right]`, we don't know which character to delete:
- Deleting `s[left]` might work
- Deleting `s[right]` might work
- One or both might create a palindrome

**Example:**
```
"abca"
 ^  ^
 a != c  (mismatch)

Try skip left: "bca" -> NOT palindrome
Try skip right: "aba" -> IS palindrome ✓
```

### 2. Critical Bug to Avoid
In the `isPalindrome` helper function, you **MUST** increment/decrement pointers:

```cpp
// WRONG - Infinite loop!
bool isPalindrome(string s, int left, int right){
    while(left < right){
        if(s[left] != s[right]){
            return false;
        }
        // Missing left++ and right--!
    }
    return true;
}

// CORRECT
bool isPalindrome(string s, int left, int right){
    while(left < right){
        if(s[left] != s[right]){
            return false;
        }
        left++;   // Don't forget!
        right--;  // Don't forget!
    }
    return true;
}
```

### 3. Edge Cases
- **Empty string:** `""` → `true` (already palindrome)
- **Single character:** `"a"` → `true` (already palindrome)
- **Two characters:** `"ab"` → `true` (delete either one)
- **Already palindrome:** `"aba"`, `"racecar"` → `true` (no deletion needed)

## Test Case Design Strategy

### 1. **Edge Cases** (boundary conditions)
```cpp
{"", true},      // Empty string
{"a", true},     // Single character
{"aa", true},    // Two same characters
{"ab", true},    // Two different characters
```

### 2. **Already Palindromes** (no deletion needed)
```cpp
{"aba", true},       // Odd length
{"abba", true},      // Even length
{"racecar", true},   // Longer palindrome
```

### 3. **Core Logic Tests**

#### a) Delete from left side
```cpp
{"abca", true}  // Delete 'c' -> "aba"
```
Tests `isPalindrome(left+1, right)` branch

#### b) Delete from right side
```cpp
{"abb", true}   // Delete last 'b' -> "ab" (then delete 'a')
```
Tests `isPalindrome(left, right-1)` branch

#### c) Delete from middle
```cpp
{"raceacar", true}  // Delete middle 'a' -> "racecar"
```

### 4. **Invalid Cases** (should return false)
```cpp
{"abc", false},        // No way to make palindrome
{"abcdef", false},     // Too many mismatches
{"abcdefdcba", false}  // More than 1 deletion needed
```

### 5. **Tricky Cases**
```cpp
{"deeee", true}  // Can delete first 'd' OR last 'e'
{"ebcbbececabbacecbbcbe", true}  // Complex real case
```

## C++ Testing Patterns Explained

### Using `pair<T1, T2>`
A `pair` holds exactly **two values** of potentially different types:

```cpp
pair<string, bool> test = {"aba", true};
//                         input  expected

string input = test.first;      // Access first element
bool expected = test.second;    // Access second element
```

**Note:** You **cannot** use `test[0]` with `pair`. Use `.first` and `.second` instead.

### Using `vector<pair<string, bool>>`
Creates a dynamic array of test cases:

```cpp
vector<pair<string, bool>> testCases = {
    {"aba", true},    // testCases[0]
    {"abc", false},   // testCases[1]
    {"abca", true}    // testCases[2]
};
```

### Range-Based For Loop with `const auto&`

```cpp
for (const auto& test : testCases) {
    string input = test.first;
    bool expected = test.second;
    // ...
}
```

**Breaking down `const auto& test`:**
- `for (... : testCases)` - "For each element in testCases"
- `test` - Variable name for current element
- `auto` - Compiler deduces type automatically (`pair<string, bool>`)
- `const` - We won't modify the test case (safer)
- `&` - Reference (don't copy, just point to original - more efficient!)

**Why use `&` (reference)?**
```cpp
// Without reference (slow)
for (const auto test : testCases) {
    // Copies the string every iteration!
}

// With reference (fast)
for (const auto& test : testCases) {
    // No copying, just points to the original
}
```

### C++17 Alternative: Structured Bindings (even cleaner!)

```cpp
for (const auto& [input, expected] : testCases) {
    // Directly unpack the pair!
    // No need for test.first or test.second
    cout << input << " -> " << expected << endl;
}
```

## Compilation and Testing

```bash
cd 680
g++ -std=c++17 -Wall solution.cpp -o solution
./solution
```

The solution includes comprehensive test cases with a test runner that reports pass/fail status for each case.

## Common Debugging Process

When tests fail:
1. **Identify which tests failed** - Run the program and note the failed cases
2. **Analyze the failure** - Compare expected vs actual output
3. **Trace manually** - Walk through the algorithm with the failed input
4. **Hypothesize the bug** - Common issues:
   - Missing pointer increments (infinite loop)
   - Off-by-one errors
   - Incorrect skip logic
5. **Add debug output** if needed - Print intermediate values
6. **Fix and re-test** - Verify all tests pass

### Example Debugging Session
If `{"eeeed", true}` fails, trace through:
```
"eeeed"
 ^   ^
 e == d? NO (mismatch)

Try skip left: "eeed" -> palindrome? YES ✓
```
