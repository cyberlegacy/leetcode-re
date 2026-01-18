/*
================================================================================
C++ GRAMMAR EXPLANATION: References (&) and const auto&
================================================================================

1. WHY USE "vector<vector<int>>& people" (Pass by Reference)?
--------------------------------------------------------------------------------

   There are 3 ways to pass parameters in C++:

   a) Pass by VALUE:    void func(vector<vector<int>> people)
      - Creates a COPY of the entire vector
      - If people has 1000 elements, it copies all 1000 elements
      - SLOW and wastes memory
      - Changes inside function do NOT affect original

   b) Pass by REFERENCE: void func(vector<vector<int>>& people)  <-- Used here
      - NO copy is made, just passes the memory address
      - FAST, O(1) time, regardless of vector size
      - Changes inside function WILL affect original
      - The & symbol means "reference to"

   c) Pass by CONST REFERENCE: void func(const vector<vector<int>>& people)
      - Same as (b), but you CANNOT modify the original
      - Best for read-only access

   In this problem, we use (b) because:
   - Avoid expensive copy (vector could be huge)
   - We modify 'people' by sorting it in-place

   Memory visualization:

   Pass by VALUE:                    Pass by REFERENCE:
   +----------+    +----------+      +----------+
   | original | -> | copy     |      | original | <-- direct access
   +----------+    +----------+      +----------+
   (2x memory)                       (no extra memory)


2. WHY USE "const vector<int>& a" in the Lambda?
--------------------------------------------------------------------------------

   sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {...});

   The comparator function is called MANY times during sorting (O(n log n) times).
   Each call compares two elements.

   - "const" = we promise NOT to modify a or b (just comparing)
   - "&" (reference) = don't copy the vectors, just reference them
   - Without &: each comparison would copy two vectors = VERY SLOW
   - With &: each comparison just passes addresses = FAST

   Example: sorting 1000 people
   - Without &: ~10,000 comparisons × 2 vector copies each = 20,000 copies!
   - With &: ~10,000 comparisons × 0 copies = 0 copies!


3. WHY USE "const auto& person" in the Range-based For Loop?
--------------------------------------------------------------------------------

   for (const auto& person : people) { ... }

   Let's break this down:

   a) "auto" - Automatic type deduction
      - Compiler figures out the type automatically
      - Here, auto = vector<int> (each element in people)
      - Saves typing and makes code cleaner
      - Equivalent to: for (const vector<int>& person : people)

   b) "&" (reference) - No copying
      - Without &: for (auto person : people)
        → Creates a COPY of each vector<int> in every iteration
        → If 1000 people, creates 1000 copies!

      - With &: for (auto& person : people)
        → Just references each element, no copy
        → MUCH faster

   c) "const" - Read-only access
      - We only READ person[1] to get the index
      - We don't modify person
      - "const" tells compiler: "I won't change this"
      - Helps catch bugs if you accidentally try to modify

   Comparison:
   +----------------------------------+--------+------------+
   | Syntax                           | Copies | Modifiable |
   +----------------------------------+--------+------------+
   | for (auto person : people)       | YES    | copy only  |
   | for (auto& person : people)      | NO     | YES        |
   | for (const auto& person : people)| NO     | NO         | <-- Best for read-only
   +----------------------------------+--------+------------+


4. SUMMARY - When to Use What?
--------------------------------------------------------------------------------

   FUNCTION PARAMETERS:
   - void func(Type x)         → Small types (int, char, bool) - copy is cheap
   - void func(Type& x)        → Large types you NEED to modify
   - void func(const Type& x)  → Large types you only READ (most common!)

   RANGE-BASED FOR LOOPS:
   - for (auto x : container)        → Small types, need a copy
   - for (auto& x : container)       → Need to MODIFY elements
   - for (const auto& x : container) → Just READING elements (most common!)

   RULE OF THUMB:
   - If it's larger than a pointer (8 bytes), use reference (&)
   - If you don't modify it, add const
   - vector, string, map, etc. are ALWAYS larger than 8 bytes → use &

================================================================================


================================================================================
PERFORMANCE ANALYSIS: Why Your Solution is 26ms but the Other is 2ms
================================================================================

THE CULPRIT: vector::insert() is EXTREMELY SLOW!

YOUR SOLUTION (SLOW - 26ms):
--------------------------------------------------------------------------------
    vector<vector<int>> result;
    for (const auto& person : people) {
        result.insert(result.begin() + person[1], person);  // <-- PROBLEM HERE!
    }

What happens inside insert():

    Before insert at position 2:  [A] [B] [C] [D] [E]
                                   0   1   2   3   4

    Step 1: Shift elements right:  [A] [B] [ ] [C] [D] [E]  ← Move C,D,E (3 operations)
    Step 2: Place new element:     [A] [B] [X] [C] [D] [E]

    insert() is O(n) because it must SHIFT all elements after insertion point!

    With n people:
    - 1st insert: shift 0 elements
    - 2nd insert: shift up to 1 element
    - 3rd insert: shift up to 2 elements
    - ...
    - nth insert: shift up to n-1 elements

    Total shifts = 0 + 1 + 2 + ... + (n-1) = n(n-1)/2 = O(n²)

    PLUS: Vector may need to REALLOCATE memory multiple times as it grows!
    Each reallocation copies ALL existing elements to new memory location.


THE FASTER SOLUTION (2ms):
--------------------------------------------------------------------------------
    vector<vector<int>> sol(n);      // Pre-allocate ONCE with exact size
    vector<bool> taken(n, false);    // Track which slots are used

    for (int i = 0; i < n; i++) {
        int h = people[i][0], k = people[i][1];
        int tmpK = k;
        for (int j = 0; j < n; j++) {
            if (taken[j]) continue;      // Skip occupied slots
            if (tmpK-- > 0) continue;    // Count k empty slots
            taken[j] = true;             // Mark as occupied
            sol[j] = {h, k};             // Direct assignment O(1)!
            break;
        }
    }

Why it's faster:
    1. NO REALLOCATION: vector<vector<int>> sol(n) allocates exact size upfront
    2. NO SHIFTING: sol[j] = {h,k} is direct assignment, O(1)
    3. Simple operations: just bool checks and integer decrements


TIME COMPLEXITY COMPARISON:
--------------------------------------------------------------------------------
                        Your Solution          Faster Solution
    Memory Allocation:  Multiple reallocs      One-time O(n)
    Per Insert:         O(n) shift             O(n) find slot
    Total:              O(n²) with high        O(n²) with low
                        constant factor        constant factor

    Both are O(n²), but constant factors matter A LOT!

    Your solution's hidden costs:
    - Memory reallocation overhead
    - Cache misses when shifting large vectors
    - Each shift moves entire vector<int> objects (not just pointers)

    Faster solution's advantages:
    - Cache-friendly sequential access
    - Simple bool/int operations
    - No memory movement


VISUAL COMPARISON:
--------------------------------------------------------------------------------

YOUR APPROACH (insert-based):

    Insert person at position k:
    [█][█][█][ ][ ][ ]    ←  result so far
             ↑
          insert here
    [█][█][█][ ][ ][ ][ ] ←  must shift everything right first!
    [█][█][█][X][ ][ ][ ] ←  then place new element

    Memory: [■■■■■■░░░░░░░░░░░░░░░] → [■■■■■■■■■░░░░░░░░░░░░░░░] (may reallocate)


FASTER APPROACH (slot-finding):

    Pre-allocated array with "taken" tracker:
    sol:   [ ][ ][ ][ ][ ][ ]    ← All slots ready
    taken: [F][F][F][F][F][F]    ← All false

    Place person with k=2 (need 2 empty slots before):
    Find 3rd empty slot (skip 2):  0   1   2  ← slot 2 is our target
    sol:   [ ][ ][X][ ][ ][ ]    ← Direct assignment
    taken: [F][F][T][F][F][F]    ← Mark as taken

    No shifting, no reallocation!


LESSON LEARNED:
--------------------------------------------------------------------------------
    vector::insert() in a loop = SLOW (O(n) per insert → O(n²) total)
    Pre-allocate + direct index = FAST

    Other slow vector operations to avoid in loops:
    - insert()     O(n)
    - erase()      O(n)
    - push_front() O(n) - doesn't exist, but insert(begin()) does this

    Fast vector operations:
    - push_back()  O(1) amortized
    - pop_back()   O(1)
    - operator[]   O(1)
    - back()       O(1)

================================================================================
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // & here: avoid copying the input vector (could be huge)
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {

        // const vector<int>& : avoid copying during each comparison, const = read-only
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] > b[0];  // Taller first
            return a[1] < b[1];                     // Same height: smaller k first
        });

        vector<vector<int>> result;

        // const auto& : auto deduces vector<int>, & avoids copy, const = read-only
        for (const auto& person : people) {
            // Insert person at index k
            result.insert(result.begin() + person[1], person);
        }

        return result;
    }
};
