## Homework: Count inversions

An inversion is a pair of values that are out of order: a value at an earlier index that is larger than a value at a later index. The list {5, 1, 4, 2, 3} has six inversions, one for each of these pairs: (5, 1), (5, 4), (5, 2), (5, 3), (4, 2), and (4, 3).

Insertion sort makes one move for each inversion, since every move swaps an out-of-order pair. So the number of inversions is also the number of moves insertion sort makes.

The program should:

* write `countInversions(const std::vector<int>& values)`, which checks every pair of positions with two nested loops, and returns the number of inversions
* write a copy of insertion sort, `insertionMoves(std::vector<int> values)`, which returns the number of moves it makes; take the list by value, so the caller's list is unchanged
* print the count from each function for the list {5, 1, 4, 2, 3}, and say whether they match

### What to check

The output should be:

```
Inversions: 6
Insertion sort moves: 6
Match: yes
```

Then try a list that is already in order, such as {1, 2, 3, 4, 5}. Both numbers should be 0.

### Extensions

* Count the comparisons that the nested loops make for a list of n values. Say how that count compares with insertion sort's comparisons in the worst case.
* Explain why the nested loop is O(n²), and what a merge-sort-based count would cost instead. You don't need to write it; the merge sort step shows the approach.

---

*This exercise is not from the book. It practices the ideas in Chapter 16.*
