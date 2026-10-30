## Homework: Lower bound

The standard library's `std::lower_bound` returns the position of the first value that is not smaller than a target. When the list has repeated values, this is the first of them, which the library call `binary_search` doesn't tell you. In this exercise, you write that search yourself.

Write `lowerBound(const std::vector<int>& values, int target)`, which returns the index of the first value that is not smaller than `target`, or the size of the list when every value is smaller. Use binary search: keep a range of indexes, check its middle, and throw away the half that can't contain the answer.

The list must be sorted, and it may repeat values. For the list {1, 3, 3, 3, 5, 8}:

* the target 3 gives index 1, the first of the three 3s
* the target 4 gives index 4, the position of the 5
* the target 9 gives index 6, the size of the list, since every value is smaller

The program should print each answer, and check it against `std::lower_bound` for the same list.

### What to check

The output should be:

```
lowerBound(3): 1
lowerBound(4): 4
lowerBound(9): 6
Matches std::lower_bound: yes
```

The duplicated 3s are the test that matters most. A search that stops at the first 3 it finds, rather than the first one in the list, will print 2 or 3.

### Extensions

* Write the same function with a loop that keeps `high` as the position just past the range, so the range is never empty and the update rules are simpler. Compare how the two versions handle a target smaller than every value.
* Explain why this search makes about log₂n comparisons, and why it still works when the list has duplicates.

---

*This exercise is not from the book. It practices the ideas in Chapter 16, with the binary search from the binary search step.*
