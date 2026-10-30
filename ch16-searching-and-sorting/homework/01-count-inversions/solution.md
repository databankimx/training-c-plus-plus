## Solution: Count inversions

The brute-force count checks every pair of positions, with the outer loop at `i` and the inner loop at `j` running from `i + 1` to the end. Each pair is counted once, with the earlier position first. Two nested loops over n values make about n(n - 1) / 2 checks, so the count is O(n²).

The insertion sort copy takes its list by value. That gives it its own copy to change, so the list in `main` is still in its original order when the brute-force count runs. The order of the two calls doesn't matter for the answer, but the by-value parameter keeps the functions independent, which is the safer design.

The two numbers match because of how insertion sort works. Each move swaps one adjacent pair that is out of order, and each such swap removes exactly one inversion from the list. The list ends with no inversions, so the number of moves is the number of inversions it started with.

For the sorted list {1, 2, 3, 4, 5}, both numbers are 0, since there are no out-of-order pairs and no moves.
