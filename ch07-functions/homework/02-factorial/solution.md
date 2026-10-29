## Solution: Factorial

The recursive version reduces the problem one step at a time. `factorialRecursive(5)` is `5 * factorialRecursive(4)`, which is `5 * 4 * factorialRecursive(3)`, and so on until the base case returns 1. The base case is what stops the calls, so it has to be reached for every input. For n of 0 or 1, the function returns 1 straight away, which is why 0! comes out as 1 without any special handling.

The loop version starts with `result` at 1, and multiplies it by each number from 2 up to n. For n of 0 or 1, the loop doesn't run, so the result stays 1, and the two versions agree.

The `main` function uses the conditional operator to print a label. Both versions are called on every input, so a disagreement would show on its own line.

For the extension, 13! is 6,227,020,800, which is larger than the largest `int` on most systems. A signed overflow is undefined behavior, so the output can't be trusted. A `long long` holds values up to about nine quintillion, which is enough for 13! and 20!. The efficiency chapter returns to how the two versions compare as n grows.
