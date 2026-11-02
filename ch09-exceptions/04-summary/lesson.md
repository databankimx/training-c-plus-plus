## Summary: Exceptions

This chapter covered how a program reports and handles errors that stop its normal flow.

* **`throw` ends the normal flow.** Nothing after the throw runs, and control passes to the nearest matching `catch`.
* **A `catch` matches by type.** `catch (int code)` handles a thrown `int`, and any other type passes on to another catch, or ends the program.
* **Exceptions cross function boundaries.** The throw can be in a function called from the try block, and the catch can be further up the call chain.
* **Error codes say little.** A number needs a lookup, and two different causes can share a code.
* **Standard exceptions carry a message.** `std::invalid_argument`, `std::out_of_range`, `std::logic_error`, and `std::runtime_error` each name a category, and `what()` returns the text.
* **Catch by `const` reference.** `catch (const std::exception& error)` handles every standard exception without copying it.
* **Avoid `catch (...)` except at the top level.** It can't report what happened.

### Check your understanding

*These questions are written for this course.*

````quiz
What happens to the statements in a try block after a throw?
○ They all run, and the throw is ignored.
→ Not quite. A throw ends the try block at that point.
◉ They are skipped, and control moves to the first matching catch.
→ Yes. Nothing after the throw runs, in the function or the block that threw.
○ They run after the catch block.
→ Not quite. The catch runs in place of the skipped statements, and they do not run later.
````

````quiz
Which catch is the best choice for a standard exception that should report its message?
○ catch (...)
→ Not quite. It has no name for the exception, so it can't report the message.
◉ catch (const std::exception& error)
→ Yes. It handles the standard exception types, and error.what() gives the message.
○ catch (int error)
→ Not quite. A standard exception object is not an int, so this catch won't match it.
````

````quiz
Why is an error code such as -2 harder to maintain than a standard exception?
○ Because codes can't be caught at all.
→ Not quite. They can be caught, but they carry no description.
◉ Because the code gives no description, and the same number can mean different things in different places.
→ Yes. A reader has to look up the meaning, and nothing stops reuse.
○ Because codes are slower to throw.
→ Not quite. The cost of throwing a code is not the problem.
````
