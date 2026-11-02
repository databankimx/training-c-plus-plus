## Solution: Swap with pointers

The example takes the addresses of `a` and `b` with `&` in the call. Inside `swapValues`, each parameter is a pointer, so `*x` and `*y` reach the caller's variables and change them. The swap uses a third variable, `temp`, which holds `*x` before it's overwritten.

The reference version from the functions chapter has the same job, but the caller can't see from the call that its arguments might change. With `swapValues(&a, &b)`, the `&` shows the reader that the variables are passed by address. That's the trade-off between the two: the pointer version makes the change visible at the call site, and the reference version makes the function body shorter.

Equal values need no special handling. Swapping 5 with 5 leaves both as 5, and the printed result is correct.
