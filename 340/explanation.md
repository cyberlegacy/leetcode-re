# 340. Longest Substring with At Most K Distinct Characters

## Problem

Given a string `s` and an integer `k`, return the length of the longest substring containing at most `k` distinct characters.

## Approach: Sliding Window

Maintain a window `[left, right]` that always contains at most `k` distinct characters.

1. Move `right` from left to right and add each character to a frequency map.
2. If the window contains more than `k` distinct characters, move `left` forward until it becomes valid again.
3. After the window is valid, update the longest length seen so far.

The frequency map is important because removing one occurrence of a character does not necessarily remove that character from the window. We erase a character only when its frequency reaches zero.

### Example

For `s = "eceba"` and `k = 2`:

```text
Window       Distinct characters   Best length
e            {e}                   1
ec           {e, c}                2
ece          {e, c}                3
eceb         {e, c, b}             invalid
ceb          {c, e, b}             invalid
eb           {e, b}                2
```

The longest valid substring is `"ece"`, so the answer is `3`.

## Correctness

At every step, the inner loop removes characters from the left while there are more than `k` distinct characters. Therefore, after the loop, the current window is valid.

For each `right` endpoint, the algorithm keeps the largest valid window ending at `right`: it removes only the minimum prefix needed to restore validity. Since every possible right endpoint is considered, taking the maximum window length produces the longest valid substring.

## Complexity

- **Time:** `O(n)`, because both pointers move only forward.
- **Space:** `O(min(n, k))` for the frequency map.
