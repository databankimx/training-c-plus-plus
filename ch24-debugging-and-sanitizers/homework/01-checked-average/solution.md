## Solution: Checked average

The assertion at the top of `average` states the caller's promise. An empty list has no average, and dividing by its size would divide by zero. In a Debug build, a caller who breaks the promise stops the program at the call, with a message naming the condition.

The sum uses `long long`, so a large list can't overflow an `int` while it's being added. The division converts both values to `double` first, so the result keeps its fraction. Dividing two `int` values would cut 5.5 to 5.

For the first extension, an empty vector stops the program at the assertion, and the exit code is non-zero. The bug is in the caller, which passed a list it should have checked, so the fix belongs there.

For the second extension, an exception is the right choice when the caller can legitimately pass an empty list, such as a list read from a file that may be empty. The caller can then catch the exception and report the problem, instead of stopping the program. The assertion is right when the caller is never supposed to pass one.
