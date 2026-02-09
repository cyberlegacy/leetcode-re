# 524. Longest Word in Dictionary through Deleting

## Problem
Given a string `s` and a string array `dictionary`, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

## Approach

### Two-Pointer Subsequence Checking

The key insight is to check if each word in the dictionary is a **subsequence** of string `s`.

**Algorithm:**
1. Initialize `result = ""` to store the best word found so far
2. For each word in the dictionary:
   - Check if it's a subsequence of `s` using the `isSubsequence` helper
   - If valid, compare with current result:
     - Update if the word is **longer** than result
     - Update if the word has **same length but is lexicographically smaller**
3. Return the result

### Subsequence Check Algorithm (`isSubsequence`)

Use two pointers to check if `word` is a subsequence of `s`:

```cpp
bool isSubsequence(string s, string word) {
    size_t i = 0;  // pointer for s
    size_t j = 0;  // pointer for word

    while(i < s.size() && j < word.size()) {
        if(s[i] == word[j]) {
            j++;  // Found a match, move word pointer
        }
        i++;  // Always move s pointer
    }

    return j == word.size();  // Did we match all characters in word?
}
```

**Example:**
```
s = "abpcplea"
word = "apple"

i=0, j=0: s[0]='a' == word[0]='a' ✓ → j=1
i=1, j=1: s[1]='b' != word[1]='p' ✗
i=2, j=1: s[2]='p' == word[1]='p' ✓ → j=2
i=3, j=2: s[3]='c' != word[2]='p' ✗
i=4, j=2: s[4]='p' == word[2]='p' ✓ → j=3
i=5, j=3: s[5]='l' == word[3]='l' ✓ → j=4
i=6, j=4: s[6]='e' == word[4]='e' ✓ → j=5
j == word.size() → true!
```

## Time Complexity
- **Subsequence check:** O(|s| + |word|)
- **For all words:** O(n × (|s| + avg_word_length))
- Where n = number of words in dictionary
- **Total:** O(n × |s|) - optimal for this problem

## Space Complexity
**O(1)** - Only storing the result string and loop variables.

## Key Insights

### 1. Why We Need Lexicographical Comparison

**Common Mistake:**
```cpp
// WRONG: Only checks if word is longer
if(isSubsequence(s, word) && word.size() > result.size()) {
    result = word;
}
```

**Problem:** When two valid words have the **same length**, we must pick the lexicographically smallest one.

**Correct:**
```cpp
if(isSubsequence(s, word)) {
    if(word.size() > result.size() ||
       (word.size() == result.size() && word < result)) {
        result = word;
    }
}
```

**Example:**
```
s = "abpcplea"
dictionary = ["ale", "ape", "abc"]  // All length 3, all valid

Without lexicographical check: might return "ale" (first found)
With lexicographical check: returns "abc" ✓ (smallest)
```

### 2. Dictionary Iteration Order

**Important:** `for(auto& word : dictionary)` iterates in **insertion order**, NOT sorted order!

```cpp
vector<string> dictionary = {"zebra", "apple", "dog"};

for(auto& word : dictionary) {
    cout << word << " ";
}
// Output: zebra apple dog
// NOT: apple dog zebra
```

This is why we must compare each word as we find it, rather than relying on any ordering.

### 3. Alternative Approach: Pre-sort Dictionary

You could pre-sort the dictionary to simplify logic:

```cpp
// Sort: longer first, then lexicographically
sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b) {
    if (a.length() != b.length()) return a.length() > b.length();
    return a < b;
});

// Now just return first valid word
for(auto& word : dictionary) {
    if(isSubsequence(s, word)) {
        return word;  // First valid = best!
    }
}
```

**Trade-off:**
- Adds O(n log n) sorting time
- Our inline comparison approach is O(n) - more efficient!

## Understanding `size_t` Type

### What is `size_t`?

`size_t` is an **unsigned integer type** designed to represent sizes and counts.

**Properties:**
- **Always unsigned** (0, 1, 2, 3... never negative)
- **Platform-dependent size:**
  - 32-bit systems: typically 32-bit (0 to ~4.2 billion)
  - 64-bit systems: typically 64-bit (0 to ~18 quintillion)
- **Guaranteed to hold any array/string size**

**Where you see `size_t`:**
```cpp
string s = "hello";
vector<int> vec = {1, 2, 3};

s.size()        // Returns: size_t
vec.size()      // Returns: size_t
sizeof(int)     // Returns: size_t
```

### Why the Compiler Warned

**Original code:**
```cpp
int i = 0;
while(i < s.size() && j < word.size()) {
//     ~~^~~~~~~~~~
// warning: comparison of different signedness
```

**The problem:**
```cpp
int i = 0;           // signed integer (-2, -1, 0, 1, 2...)
s.size()             // returns size_t (unsigned: 0, 1, 2, 3...)

i < s.size()         // ⚠️ Comparing signed vs unsigned!
```

### Why Mixing Signed/Unsigned is Dangerous

**Example of the bug:**
```cpp
int i = -1;              // Negative number
size_t size = 5;

if (i < size) {
    cout << "i is less";
} else {
    cout << "i is NOT less";  // This prints! 😱
}
```

**Why?** When comparing, `-1` gets converted to unsigned:
- `-1` as binary: `11111111 11111111 11111111 11111111`
- Interpreted as unsigned: `4,294,967,295` (huge!)
- So `-1 < 5` becomes `4,294,967,295 < 5` → **false!**

### The Fix: Use `size_t`

```cpp
// ✓ CORRECT: Both unsigned
size_t i = 0;
size_t j = 0;
while(i < s.size() && j < word.size()) {
    // ...
}
```

### Real-World Bug Example

```cpp
void processLastN(string s, int n) {
    // Try to process last n characters
    for(int i = s.size() - n; i < s.size(); i++) {
        cout << s[i];
    }
}

processLastN("hello", 10);  // n > s.size()
// s.size() - n = 5 - 10 = -5
// -5 converted to unsigned = huge number
// Loop runs billions of times! 💥
```

**Fixed with `size_t`:**
```cpp
void processLastN(string s, size_t n) {
    size_t start = (n > s.size()) ? 0 : s.size() - n;
    for(size_t i = start; i < s.size(); i++) {
        cout << s[i];
    }
}
```

### When to Use Each Type

| Type | Use When | Example |
|------|----------|---------|
| `int` | General integers, can be negative | `int temperature = -5;` |
| `size_t` | Sizes, counts, array indices | `size_t i = 0; i < vec.size()` |
| `unsigned int` | Never negative, smaller range | `unsigned int age = 25;` |
| `long long` | Very large numbers | `long long factorial = 1000000000000LL;` |

### Best Practice

**For loop indices with `.size()`:**
```cpp
// ✓ GOOD: Match types
for(size_t i = 0; i < s.size(); i++) {
    cout << s[i];
}

// ✗ BAD: Mixed signedness
for(int i = 0; i < s.size(); i++) {
    cout << s[i];
}
```

## Test Case Design Strategy

### 1. **Basic Functionality**
```cpp
{"abpcplea", {"ale","apple","monkey","plea"}, "apple"}
```
Tests the core subsequence checking and length comparison.

### 2. **Lexicographical Order (Critical!)**
```cpp
{"abpcplea", {"ale", "ape", "abc"}, "abc"}
```
All three are valid and same length → must pick "abc" (smallest).

### 3. **Edge Cases**
- Empty dictionary: `{"abpcplea", {}, ""}`
- Empty string s: `{"", {"a", "b"}, ""}`
- No valid subsequence: `{"abpcplea", {"xyz", "monkey"}, ""}`
- Single character: `{"a", {"a", "b", "c"}, "a"}`

### 4. **Same Length Comparisons**
```cpp
{"abcde", {"ace", "acd", "ade", "bde"}, "acd"}
```
Multiple valid words of same length → test lexicographical ordering.

### 5. **Order in Dictionary**
```cpp
{"abpcplea", {"ale", "apple"}, "apple"}  // Longer comes second
{"abpcplea", {"apple", "ale"}, "apple"}  // Longer comes first
```
Result should be same regardless of order in dictionary.

### 6. **Complex Subsequences**
```cpp
{"aewbcnpoiu", {"apple", "ewcn", "ahbgdc", "npui"}, "ewcn"}
```
Tests correct subsequence checking with complex patterns.

### 7. **Special Cases**
- Exact match: `{"abc", {"abc"}, "abc"}`
- Repeated characters: `{"aaaa", {"aa", "aaa", "a", "aaaa"}, "aaaa"}`
- Duplicates in dictionary: `{"abc", {"ac", "ab", "ac"}, "ab"}`

## Compilation and Testing

```bash
cd 524
g++ -std=c++17 -Wall solution.cpp -o solution
./solution
```

The solution includes 19 comprehensive test cases covering all edge cases and scenarios.

## Summary

- **Core algorithm:** Two-pointer subsequence checking
- **Critical detail:** Must compare both length AND lexicographical order
- **Efficiency:** O(n × |s|) time, O(1) space - optimal
- **Type safety:** Use `size_t` for indices to match `.size()` return type
- **Testing:** Cover edge cases, lexicographical ties, and order independence
