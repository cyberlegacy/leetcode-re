# 763. Partition Labels

## Problem

Given a string `s`, partition it into as many parts as possible so that each letter appears in at most one part. Return a list of integers representing the size of these parts.

## Approach: Greedy with Last Occurrence Tracking

### Key Insight

For a valid partition, every character that appears in that partition must have all its occurrences contained within that same partition. This means the partition must extend at least to the last occurrence of every character it contains.

### Algorithm

1. **Precompute last occurrences**: First pass through the string to record the last index where each character appears.

2. **Greedy partitioning**: Second pass to form partitions:
   - Track `start` (beginning of current partition) and `end` (minimum required end).
   - For each character at index `i`, extend `end` to be at least the last occurrence of that character.
   - When `i == end`, we've found a valid partition boundary. Record its size and start a new partition.

### Why This Works

- We greedily try to end each partition as early as possible.
- By always extending `end` to cover the last occurrence of each character we encounter, we guarantee all occurrences of every character in the partition are included.
- When we reach `end`, no character we've seen requires us to go further, so we can safely cut.

## Complexity

- **Time**: O(n) - Two passes through the string
- **Space**: O(1) - Fixed array of 26 integers for last occurrences

## Example

```
Input: s = "ababcbacadefegdehijhklij"

Last occurrences:
a -> 8, b -> 5, c -> 7, d -> 14, e -> 15, f -> 11, g -> 13, h -> 19, i -> 22, j -> 23, k -> 20, l -> 21

Partitioning:
- i=0 (a): end = max(0, 8) = 8
- i=1 (b): end = max(8, 5) = 8
- i=2 (a): end = max(8, 8) = 8
- ...
- i=8 (a): end = 8, i == end, partition [0,8] has size 9
- i=9 (d): start=9, end = max(9, 14) = 14
- ...
- i=15 (e): end = 15, i == end, partition [9,15] has size 7
- i=16 (h): start=16, end = max(16, 19) = 19
- ...
- i=23 (j): end = 23, i == end, partition [16,23] has size 8

Output: [9, 7, 8]
```
