# 142. Linked List Cycle II

## Problem
Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return `null`.

## Approach: Floyd's Cycle Detection (Tortoise and Hare)

### Step 1: Detect if a cycle exists
Use two pointers:
- **Slow pointer**: moves 1 step at a time
- **Fast pointer**: moves 2 steps at a time

If there's a cycle, they will eventually meet inside the cycle.

### Step 2: Find the cycle start node
Once they meet, reset one pointer to `head` and move both pointers 1 step at a time. The node where they meet again is the cycle start.

## Why Does This Work?

### Setup
```
head ----L---- [cycle start] ----K---- [meeting point]
                     |                       |
                     +--------(C - K)--------+

L = distance from head to cycle start
C = cycle length
K = distance from cycle start to meeting point
```

### Phase 1: Finding the meeting point

When slow and fast meet inside the cycle:
- Slow traveled: `L + K` steps
- Fast traveled: `L + K + nC` steps (fast completed n extra laps around the cycle)

Since fast moves **twice as fast** as slow, in the **same amount of time**, fast travels **twice the distance**:

```
Fast distance = 2 × Slow distance
L + K + nC = 2(L + K)
L + K + nC = 2L + 2K
nC = L + K
L = nC - K          <-- This is the key equation!
```

### Phase 2: Why do they meet at cycle start?

Now we reset pointer A to `head`, keep pointer B at `meeting point`, and move both 1 step at a time.

**After L steps:**
- Pointer A: starts at head, travels L steps → arrives at **cycle start**
- Pointer B: starts at meeting point (which is K steps into the cycle), travels L steps

Where does pointer B end up after L steps?

Since `L = nC - K`, pointer B travels `nC - K` steps:
```
B's position = K + (nC - K) = nC = n full cycles
```

After n full cycles, B is back at the **cycle start**!

**Both pointers arrive at the cycle start after exactly L steps. That's where they meet.**

## Complexity
- **Time**: O(n) - each pointer traverses at most the entire list
- **Space**: O(1) - only two pointers used

## Key Insights
1. The mathematical proof is the core of this problem - understanding why the algorithm works
2. If fast reaches `null`, there's no cycle
3. This is a classic two-pointer technique problem
4. The same detection method applies to finding duplicate numbers (Problem 287)
