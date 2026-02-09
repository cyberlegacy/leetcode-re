# 633. Sum of Square Numbers

## Problem
Given a non-negative integer `c`, decide whether there are two integers `a` and `b` such that `a² + b² = c`.

## Approach

### Two-Pointer Technique
We use a two-pointer approach to efficiently search for a valid pair:

1. Initialize `left = 0` and `right = √c`
2. While `left ≤ right`:
   - Calculate `sum = left² + right²`
   - If `sum == c`, we found a valid pair, return `true`
   - If `sum < c`, increment `left` (need a larger sum)
   - If `sum > c`, decrement `right` (need a smaller sum)
3. If no valid pair is found, return `false`

### Why Start `left = 0`?
Zero is a valid square (0² = 0). Many numbers can be expressed as `0² + b² = c` (perfect squares like 4, 9, 16, etc.). If we start at `left = 1`, we miss these cases.

**Example where `left = 1` fails:**
- `c = 4`: The valid answer is `0² + 2² = 4`
- Starting at `left = 1` would try `1² + 2² = 5` (wrong!)

## Time Complexity
**O(√c)** - In the worst case, we traverse from 0 to √c.

## Space Complexity
**O(1)** - Only using a constant amount of extra space.

## Key Insights

### 1. Why Use `long` Type?
Even though `c` is an `int`, we need `long` for `left`, `right`, and `sum` to prevent integer overflow during multiplication.

**The Problem:**
```cpp
int right = 46340;  // √(INT_MAX) ≈ 46340
int sum = right * right;  // This is fine
// But when both left and right are large:
int left = 40000, right = 40000;
int sum = left * left + right * right;  // Overflow! Could exceed INT_MAX
```

**Type Promotion Rule:**
```cpp
int left = 50000;
long sum = left * left;  // WRONG! Overflow happens BEFORE conversion to long
```
The multiplication `left * left` is computed as `int × int = int` first, overflows, then gets converted to `long`.

**Correct Solution:**
```cpp
long left = 0;        // Declare as long from the start
long right = sqrt(c);
long sum = left * left + right * right;  // All operations are long
```

### 2. When to Use `long long`?
- `int`: 32-bit, range ≈ -2.1B to 2.1B
- `long`: Usually 64-bit on Linux/Mac, 32-bit on Windows
- `long long`: Always 64-bit, range ≈ -9.2×10¹⁸ to 9.2×10¹⁸

**Use `long long` when:**
- Products/sums might exceed 2 billion
- Need guaranteed 64-bit cross-platform
- LeetCode problems with `n ≤ 10⁹` and operations on them
- Squaring numbers > 46,340

For this problem, `long` is sufficient on most systems, but `long long` ensures portability.

## Edge Cases Tested
1. `c = 0`: 0² + 0² = 0 ✓
2. `c = 1`: 0² + 1² = 1 ✓
3. Perfect squares: 4, 9, 16, 25, 100 ✓
4. Sum of two non-zero squares: 5 (1² + 2²), 13 (2² + 3²) ✓
5. Numbers that cannot be expressed: 3, 6, 7, 999 ✓
6. Maximum int value: 2147483647 ✓

## Compilation and Testing
```bash
cd 633
g++ -std=c++17 -Wall solution.cpp -o solution
./solution
```

The solution includes comprehensive test cases with a test runner that reports pass/fail status.
