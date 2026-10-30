## Solution: Stairs

The naive version has the same shape as the Fibonacci recursion, with a different base case. Both base cases return 1 here, so the answers are the Fibonacci numbers shifted by one place: ways(n) is the Fibonacci number at position n + 1. That's why ways(10) is 89, and why the call count for n = 10 is 177, the same as the Fibonacci count.

The memoized version makes 2n − 1 calls for n of 1 or more. Each value from 2 up to n is worked out once, and each one makes two calls, plus the first call. The naive version repeats the work for each smaller value, so its count grows exponentially.

The loop extension computes the same sequence from the bottom up, keeping the last two values, as the Fibonacci step's loop did. It does n passes and no recursion, so it's the cheapest of the three.

For the second extension, both sequences grow at the same rate, since they're the same recursion with a different start. The naive count for n = 20 here is the same as the Fibonacci naive count for n = 21 in the step, because the position is shifted by one. Both grow exponentially, and both memoized counts grow linearly.
