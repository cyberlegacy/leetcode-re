# 122. Best Time to Buy and Sell Stock II

## Problem

You are given an array `prices` where `prices[i]` is the price of a stock on day `i`. You can complete as many transactions as you like (buy and sell multiple times). Find the maximum profit you can achieve.

**Note**: You cannot hold multiple stocks at once (must sell before buying again).

## Approach: Greedy - Collect All Upward Movements

### Key Insight

Since we can make unlimited transactions with no fees, the optimal strategy is simple: **capture every price increase**.

If the price goes up from day `i` to day `i+1`, we should "buy on day i, sell on day i+1" to collect that profit.

### Why This Works

Consider prices: [1, 5, 3, 6]

Two ways to think about it:

1. **Buy at 1, sell at 6**: Profit = 5
2. **Buy at 1, sell at 5, buy at 3, sell at 6**: Profit = (5-1) + (6-3) = 4 + 3 = 7

The second approach is better! By selling before a dip and buying back, we avoid the loss from 5→3.

Mathematically, any upward journey can be decomposed into daily gains:
- Going from price 1 to 6 over days [1,2,5,6] = (2-1) + (5-2) + (6-5) = sum of positive differences

So collecting all positive day-to-day differences gives us the maximum possible profit.

### Algorithm

```
profit = 0
for each consecutive day pair (yesterday, today):
    if today's price > yesterday's price:
        profit += (today - yesterday)
return profit
```

## Complexity

- **Time**: O(n) - Single pass through the array
- **Space**: O(1) - Only a few variables

## Example Walkthrough

**Input**: [7, 1, 5, 3, 6, 4]

| Day | Price | Previous | Difference | Action | Running Profit |
|-----|-------|----------|------------|--------|----------------|
| 0 | 7 | - | - | - | 0 |
| 1 | 1 | 7 | -6 | Skip (negative) | 0 |
| 2 | 5 | 1 | +4 | Add 4 | 4 |
| 3 | 3 | 5 | -2 | Skip (negative) | 4 |
| 4 | 6 | 3 | +3 | Add 3 | 7 |
| 5 | 4 | 6 | -2 | Skip (negative) | 7 |

**Output**: 7

This is equivalent to: Buy at 1, sell at 5 (profit 4), buy at 3, sell at 6 (profit 3).
