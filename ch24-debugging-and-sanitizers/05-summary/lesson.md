## Summary: Debugging and sanitizers

This chapter covered the tools for finding bugs once a program is written, and what each one can and can't show.

* **A stack trace shows how the program got somewhere.** `std::stacktrace::current()` captures the calls in progress, and the Backtrace option adds the names.
* **Capture traces where errors are reported.** Capturing them on every call costs time and memory.
* **An assertion checks a promise the code makes to itself.** A failed assertion is a bug, and it's removed in release builds by `NDEBUG`.
* **Assertions are not input checks.** User input needs an error path, such as an exception, not an assertion.
* **A debugger stops the program and shows its values.** Breakpoints, stepping, and the variables panel find where values go wrong.
* **Off-by-one errors live at loop boundaries.** Check the boundary condition first.
* **Sanitizers find memory errors and undefined behavior while the program runs.** AddressSanitizer, UndefinedBehaviorSanitizer, and ThreadSanitizer each cover a different kind of mistake.
* **Sanitizers need a supporting toolchain.** This course's MSYS2 UCRT64 setup doesn't package them, so the chapter explains them without running them.

### Check your understanding

*These questions are written for this course.*

````quiz
What does a failed assertion tell you?
○ That the user typed an invalid value.
→ Not quite. A bad input is handled with an error path, not an assertion.
◉ That the code broke a promise it makes to itself, which is a bug to fix.
→ Yes. An assertion states a condition that must hold if the code is correct.
○ That the program is running too slowly.
→ Not quite. Assertions check conditions, not speed.
````

````quiz
Which tool finds an out-of-range array write while the program runs?
○ A stack trace.
→ Not quite. A stack trace shows the calls, not the memory being written.
◉ AddressSanitizer, on a toolchain that supports it.
→ Yes. It reports the write and the line where it happened.
○ A release build.
→ Not quite. Release builds are faster, but they don't check memory.
````

````quiz
An off-by-one error is most likely to be found where?
○ In the output formatting.
→ Not quite. Output formatting rarely causes an off-by-one.
◉ At the boundary condition of a loop, where the first and last values are decided.
→ Yes. The boundary is the first place to check.
○ In the header file.
→ Not quite. Headers rarely hold loop boundaries.
````
