## Solution: Safe age

The loop runs until the age is valid. Each pass tries to read an age inside a `try` block. A failed read throws `std::invalid_argument`, after `clear` and `ignore` have prepared the stream for another attempt. A number out of range throws `std::out_of_range`. Both are caught by one `catch (const std::exception& error)`, which prints the message and lets the loop go around again.

The `break` is reached only when the age is accepted, so the loop ends exactly when the input is good. Putting the `break` at the end of the `try` block means an exception skips it, which is what keeps the loop going.

The clear-and-ignore step is what the Battleship program needed. Without it, the failed read leaves the stream in its error state, and every later read fails at once, so the messages repeat forever.

Catching the base class `std::exception` is enough here, since both messages are used the same way. The first extension shows when a separate catch for each type becomes worth the extra code.
