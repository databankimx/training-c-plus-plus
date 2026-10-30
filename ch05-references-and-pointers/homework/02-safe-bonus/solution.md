## Solution: Safe bonus

The example checks for `nullptr` first, and returns early if the pointer is empty. Only after that check does it dereference the pointer with `*score += bonus`. Reversing the two steps would read through a null pointer when the caller passes `nullptr`, which is undefined behavior and usually a crash.

The early `return` keeps the function's main path flat. Each condition is handled once, at the top, and the rest of the function can assume it has a valid pointer.

In `main`, the second call passes `nullptr` directly. The function prints its message, and `points` stays at 60. That shows the function refuses to act when it has nothing to act on, rather than guessing.
