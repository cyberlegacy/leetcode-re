# 76. Minimum Window Substring

## What is Sliding Window?

Sliding Window is a technique for solving problems that involve **contiguous sequences** (subarrays or substrings). Instead of checking every possible substring (brute force), you maintain a "window" defined by two pointers — `left` and `right` — and slide them across the data.

Think of it like looking through a physical window on a long wall of letters:

```
String:  A D O B E C O D E B A N C
         ^                       ^
       left                    right
         |_______ window _______|
```

You can:
- **Expand** the window by moving `right` forward (see more)
- **Shrink** the window by moving `left` forward (see less)

### Why is it efficient?

A brute force approach checks **all** possible substrings — that's O(n^2). Sliding window only moves each pointer forward, never backward. Each element is visited at most twice (once by `right`, once by `left`), so it runs in **O(n)**.

### When to use it?

Sliding window works when the problem asks for:
- Minimum/maximum length subarray or substring satisfying some condition
- Longest substring with at most K distinct characters
- Smallest window containing all required elements (like this problem)

The general pattern is:
1. Move `right` to expand until the window satisfies the condition
2. Move `left` to shrink while the condition is still met (to find the optimal)
3. Repeat until `right` reaches the end

---

## Problem
Given strings `s` and `t`, find the minimum window substring of `s` that contains every character in `t` (including duplicates). Return `""` if no such window exists.

## Approach: Sliding Window

The core idea is to maintain a window `[left, right)` over `s` and slide it:

1. **Expand** — Move `right` to include more characters until the window contains all characters of `t`.
2. **Shrink** — Move `left` to make the window as small as possible while it still satisfies the requirement.
3. **Record** the smallest valid window seen.

### Key Details

- Use a hash map `need` to store the required count of each character in `t`.
- Use a hash map `window` to track counts of characters inside the current window.
- A counter `valid` tracks how many *distinct* characters have met their required count. When `valid == need.size()`, the window is valid.

### Walkthrough with `s = "ADOBECODEBANC"`, `t = "ABC"`

```
need: {A:1, B:1, C:1}

Expand right until valid:
  ADOBEC        — contains A,B,C → valid, record len=6
Shrink left:
  DOBEC         — missing A → stop shrinking, keep expanding
  ...
  BANC          — contains A,B,C → valid, record len=4 (better)
  ANC           — missing B → stop
```

Result: `"BANC"`

## Complexity

- **Time:** O(|s| + |t|) — each character is visited at most twice (once by `right`, once by `left`).
- **Space:** O(|s| + |t|) — for the hash maps (at most the size of the character set).
