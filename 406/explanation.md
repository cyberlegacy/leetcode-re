# 406. Queue Reconstruction by Height

## Problem

You have a queue of people described by `[h, k]` where:
- `h` = the person's height
- `k` = the number of people **in front** of them who have height **>= h**

Given a shuffled list, reconstruct the queue.

## Approach: Greedy - Tallest First

### Key Insight

**Process people from tallest to shortest.** When inserting a tall person, shorter people don't affect their `k` value at all (since `k` only counts people >= their height).

So if we insert tall people first, we can place them exactly at index `k` — and when we later insert shorter people, they won't disrupt the tall people's `k` counts.

### Algorithm

1. **Sort** people by:
   - Height descending (tallest first)
   - If same height, by `k` ascending (smaller k first)

2. **Insert** each person at index `k` in the result list

### Why This Works

When we insert person `[h, k]`:
- Everyone already in the list is **taller or equal** height
- There are currently `k` people before position `k`
- All those people are >= h, satisfying the k requirement
- Future insertions of shorter people won't affect this person's k count

### Step-by-Step Example

**Input**: `[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]`

**Step 1: Sort** (height desc, k asc):
```
[[7,0], [7,1], [6,1], [5,0], [5,2], [4,4]]
```

**Step 2: Insert one by one**:

| Person | Action | Result |
|--------|--------|--------|
| [7,0] | Insert at index 0 | [[7,0]] |
| [7,1] | Insert at index 1 | [[7,0], [7,1]] |
| [6,1] | Insert at index 1 | [[7,0], [6,1], [7,1]] |
| [5,0] | Insert at index 0 | [[5,0], [7,0], [6,1], [7,1]] |
| [5,2] | Insert at index 2 | [[5,0], [7,0], [5,2], [6,1], [7,1]] |
| [4,4] | Insert at index 4 | [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]] |

**Output**: `[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]`

### Verification

Let's verify each person:
- [5,0]: 0 people in front >= 5 ✓
- [7,0]: 0 people in front >= 7 (only [5,0] which is < 7) ✓
- [5,2]: 2 people in front >= 5: [7,0] and [5,0] ✓
- [6,1]: 1 person in front >= 6: [7,0] ✓
- [4,4]: 4 people in front >= 4: all of them ✓
- [7,1]: 1 person in front >= 7: [7,0] ✓

## Complexity

- **Time**: O(n²) - Sorting is O(n log n), but inserting into vector is O(n) per insert, n inserts = O(n²)
- **Space**: O(n) - For the result vector

## Why Sort Same Height by K Ascending?

For people with the same height, the one with smaller `k` should be placed first. Example:

If we have [7,0] and [7,1]:
- [7,0] must come before [7,1]
- If we inserted [7,1] first at index 1, there'd be nothing at index 0 yet — wrong!
- By processing [7,0] first, when [7,1] is inserted at index 1, [7,0] is already at index 0
