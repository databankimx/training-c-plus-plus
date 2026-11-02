## Solution: Count in range

The condition `value >= low && value <= high` includes both ends. The values 2, 3, and 4 satisfy it for the range 2 to 4, so the answer is 3, and the values 1 through 5 all satisfy it for the range 1 to 5.

The common mistake is to write `value > low && value < high`. That excludes both ends, so the range 2 to 4 counts only the value 3, and the answer is 1. The mistake is easy to miss, because the code runs and prints a plausible number. The check for the endpoints is what catches it.

For the first extension, the strict version gives 1 for the range 2 to 4, and 3 for the range 1 to 5, since 2, 3, and 4 are strictly inside it. The difference is exactly the two endpoints of each range.

For the second extension, stepping through the loop in the debugger shows the value 2 and the value 4 being tested at the boundary, and the condition's result for each one. Watching the two comparisons makes the inclusive rule visible.
