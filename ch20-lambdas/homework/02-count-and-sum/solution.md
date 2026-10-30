## Solution: Count and sum

`std::for_each` calls the lambda once for each value in the range. The lambda captures `evenCount` and `evenSum` by reference, so every call updates the variables in `main`, not copies of them.

The `value % 2 == 0` test picks out the even values: 2, 4, 6, 8, and 10. That gives a count of 5 and a sum of 30. Both totals are read after the call, so they show the work done inside the lambda.

For the first extension, a lambda with `[=]` holds copies of the two variables, and a lambda's copies are `const` unless the lambda is declared `mutable`. The statements `evenCount++` and `evenSum += value` then fail to compile. Adding `mutable` after the parameter list would let them compile, but the totals would still be the lambda's own copies, so `main` would print 0 and 0. Capturing by reference is the right choice here.

For the second extension, a loop does the same work, and its totals are visible in one place. The lambda version makes the rule a unit that could be passed to any algorithm. The loop is easier to read for a single use, and the lambda is easier to reuse.
