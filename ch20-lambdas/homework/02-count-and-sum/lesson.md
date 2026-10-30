## Homework: Count and sum

The standard algorithm `std::for_each` calls a function once for each value in a range. In this exercise, you use it with a lambda that captures two totals by reference, so the totals are available after the loop.

The program should:

* create a `std::vector<int>` holding the numbers 1 through 10
* declare two `int` variables, `evenCount` and `evenSum`, both starting at 0
* call `std::for_each` on the vector with a lambda that captures both variables by reference. The lambda adds 1 to `evenCount` and adds the value to `evenSum` only when the value is even
* print `Even count: ` followed by `evenCount`, and then `Sum of evens: ` followed by `evenSum`

### What to check

The output should be:

```
Even count: 5
Sum of evens: 30
```

The even numbers are 2, 4, 6, 8, and 10. Their sum is 30. The lambda changes the two variables through their references, so the totals are still there after `std::for_each` returns.

### Extensions

* Change the lambda to capture by copy, using `[=]` on the two variables, and predict what happens. Then explain why the totals can't be updated, and what the compiler reports.
* Replace the lambda with a loop, and compare the two versions. Which one makes it easier to see that the totals are updated?

---

*This exercise is not from the book. It practices the ideas in Chapter 20, with the vectors from Chapter 14.*
