# Problem 452: Minimum Number of Arrows to Burst Balloons

## Problem Description
Given an array of intervals `points` where `points[i] = [xstart, xend]` represents a balloon that spans horizontally from `xstart` to `xend`, find the minimum number of arrows that must be shot to burst all balloons. An arrow shot at position `x` bursts all balloons where `xstart ≤ x ≤ xend`.

## Why This Greedy Algorithm Works

### The Greedy Strategy
The algorithm uses a **greedy approach** based on sorting by **end points** and selecting the earliest ending interval first.

### Key Steps:
1. **Sort balloons by their end coordinates** (ascending order)
2. **Shoot the first arrow** at the end of the first balloon
3. **For each subsequent balloon**:
   - If it starts after the current arrow position, we need a new arrow
   - Otherwise, it overlaps with the current arrow position (no new arrow needed)

### Why Sorting by End Point is Optimal

#### The Intuition
When we sort by end points and always shoot at the earliest ending balloon:
- We maximize the chance that future balloons will overlap with our current arrow
- Shooting at the end point of the earliest-ending balloon gives us the "best coverage" for overlapping balloons

#### Proof of Correctness (Exchange Argument)

**Claim**: Sorting by end points and greedily selecting arrows gives the optimal solution.

**Proof**:
1. Let's say we have an optimal solution OPT that uses `k` arrows
2. Our greedy solution uses arrows at positions based on end points
3. Consider the first arrow in our greedy solution at position `g₁` (the end of the first balloon after sorting)

**Case 1**: If OPT also has an arrow at `g₁`, great! Both solutions agree on the first arrow.

**Case 2**: If OPT has its first arrow at some other position `o₁`:
   - Since we sorted by end points, `g₁` is the earliest end point
   - Any balloon that `o₁` bursts must have `start ≤ o₁ ≤ end`
   - For the first balloon (earliest end), we know `o₁ ≤ g₁` (otherwise the first balloon wouldn't be burst)
   - But we can **replace** `o₁` with `g₁` in OPT without losing any coverage
   - Why? Because any balloon that overlaps at `o₁` must extend at least to `g₁` (since `g₁` is the earliest end point that needs to be covered)
   - This creates a new optimal solution that agrees with our greedy choice

By induction, we can continue this argument for all subsequent arrows, proving that the greedy solution is optimal.

### Visual Example

Consider balloons: `[[10,16], [2,8], [1,6], [7,12]]`

**After sorting by end point**: `[[1,6], [2,8], [7,12], [10,16]]`

```
Balloon 1:  [1========6]
Balloon 2:     [2===========8]
Balloon 3:              [7=========12]
Balloon 4:                   [10===========16]
            0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
```

**Greedy Process**:
1. Shoot arrow at position 6 (end of first balloon)
   - Bursts: Balloon 1 [1,6] ✓
   - Bursts: Balloon 2 [2,8] ✓ (since 6 is within [2,8])
   
2. Balloon 3 [7,12] starts at 7 > 6, so we need a new arrow
   - Shoot arrow at position 12 (end of balloon 3)
   - Bursts: Balloon 3 [7,12] ✓
   - Bursts: Balloon 4 [10,16] ✓ (since 12 is within [10,16])

**Result**: 2 arrows (optimal)

### Why Not Sort by Start Point?

If we sorted by start point instead:
- We might shoot an arrow too early
- This could miss balloons that start earlier but end later
- Example: `[[1,10], [2,3]]` - shooting at 10 (end of first) covers both, but sorting by start gives the same result here

The key insight is that sorting by **end point** ensures we make the most "conservative" choice - we shoot as late as possible while still hitting the current balloon, maximizing overlap potential.

### Time Complexity: O(n log n)

Let's break down the time complexity step by step:

#### Step-by-Step Analysis

**1. Sorting Operation: O(n log n)**
```cpp
sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
});
```
- The `std::sort` function uses an efficient comparison-based sorting algorithm (typically **introsort**, which is a hybrid of quicksort, heapsort, and insertion sort)
- For `n` elements, comparison-based sorting has a **lower bound of Ω(n log n)** comparisons (proven by decision tree model)
- In the best case, `std::sort` achieves O(n log n) time complexity
- In the worst case, `std::sort` guarantees O(n log n) time complexity (unlike pure quicksort which can degrade to O(n²))
- Each comparison operation compares two integers (`a[1]` vs `b[1]`), which is O(1)
- **Total for sorting: O(n log n)**

**2. Single Pass Through Array: O(n)**
```cpp
for(int i = 1; i < points.size(); i++) {
    if(points[i][0] > end) {
        count++;
        end = points[i][1];
    }
}
```
- The loop iterates exactly `n-1` times (from index 1 to n-1)
- Each iteration performs:
  - One comparison: `points[i][0] > end` → O(1)
  - Conditional increment: `count++` → O(1)
  - Assignment: `end = points[i][1]` → O(1)
- All operations inside the loop are constant time O(1)
- **Total for the loop: O(n)**

**3. Overall Time Complexity**
- **Sorting**: O(n log n) - **Dominant term**
- **Single pass**: O(n)
- **Total**: O(n log n) + O(n) = **O(n log n)**

#### Why O(n log n) Dominates

The sorting step dominates because:
- **O(n log n) grows faster than O(n)** as n increases
- For large values of n:
  - n = 10: n log n ≈ 33, n = 10
  - n = 100: n log n ≈ 664, n = 100
  - n = 1000: n log n ≈ 9,966, n = 1,000
  - n = 1,000,000: n log n ≈ 20,000,000, n = 1,000,000

As n grows, the n log n term becomes significantly larger than n, making it the **asymptotically dominant** term.

#### Why We Can't Do Better Than O(n log n)

**Lower Bound Proof**:
- To determine the minimum number of arrows, we need to know the relative ordering of balloon end points
- This requires comparing balloons to determine their order
- Any comparison-based sorting algorithm requires at least Ω(n log n) comparisons (information-theoretic lower bound)
- Therefore, **O(n log n) is optimal** for comparison-based approaches

**Alternative Approaches**:
- If we could use **counting sort** or **radix sort** (non-comparison based), we could potentially achieve O(n) if the coordinate values are bounded
- However, for general integer coordinates (including INT_MAX), comparison-based sorting is necessary
- Even with bounded coordinates, the overhead of counting sort might not be worth it for typical problem sizes

### Space Complexity

**Auxiliary Space: O(1)**
- We only use a few variables: `count`, `end`, `i` → O(1) space
- No additional data structures are created

**Space Used by Sorting: O(log n) to O(n)**
- `std::sort` uses **in-place sorting** (modifies the input array)
- The recursion stack or iteration stack for sorting algorithms typically uses:
  - **O(log n)** space for quicksort/introsort (average case)
  - **O(n)** space in worst case (though introsort avoids this)
- This is **not counted** as auxiliary space since it's part of the sorting algorithm's internal implementation

**Total Space Complexity**: 
- **O(1)** auxiliary space (what we explicitly use)
- **O(log n)** space used by sorting algorithm (typically)

## Related Problems
- **435. Non-overlapping Intervals**: Very similar problem with the same greedy approach
- **56. Merge Intervals**: Related interval problem
- **253. Meeting Rooms II**: Interval scheduling problem

