## Solution: Safe division

`safeDivide` returns `std::nullopt` when the divisor is zero, and otherwise the quotient, which converts to an optional holding it. The return type tells the caller that the result may be missing.

Each call is checked with `if (first)` before `value()` is used. The check is what makes the program safe. `value()` throws `std::bad_optional_access` on an empty optional, and nothing in this exercise catches it, so reading the value without a check would stop the program.

The output for the three calls is `10 / 2 = 5`, `1 / 0 = no answer`, and `9 / 3 = 3`. The empty case is handled in the same place as the others, so the reader can see every path.

For the first extension, `value_or` with a fallback prints that fallback in place of the words. The fallback is a value the caller chooses. It's convenient when a default makes sense, but the words "no answer" are better when the caller must show the difference to a user.

For the second extension, an exception carries the same information, but the caller has to remember to catch it, and an uncaught exception ends the program. The optional makes the empty case part of the return type, so the compiler reminds the caller to handle it. For a result that's sometimes missing as a normal matter, the optional is easier to get right.
