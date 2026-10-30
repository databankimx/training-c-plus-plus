## Solution: Lower bound

The search keeps the range `[low, high)`, which includes `low` and excludes `high`. Starting with `high` at the size of the list means every value is in range at the start, including the case where the target is larger than all of them. The loop ends when the range is empty, and `low` is then the answer.

When the middle value is smaller than the target, every value up to the middle is also too small, so `low` moves past the middle. When the middle value is not smaller, the answer is at the middle or before it, so `high` moves to the middle. Keeping the middle in the range in that second case is what finds the first of the repeated values, rather than stopping at any 3.

For the target 3 in {1, 3, 3, 3, 5, 8}, the range shrinks from six values to three, then to one, and then the search settles on index 1. Each step halves the range, so the search takes about log₂n comparisons, the same growth as the binary search step.

The target 0 is smaller than every value, so `low` moves past every index and ends at 0, the first position. That's the case the "Try" asks about.
