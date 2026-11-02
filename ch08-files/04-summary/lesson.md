## Summary: Files

This chapter covered reading and writing files with the standard stream classes.

* **`<fstream>` provides the file stream classes.** `std::ofstream` writes, `std::ifstream` reads, and `std::fstream` does both.
* **File streams work like `cout` and `cin`.** The `<<` and `>>` operators, and `std::getline`, all apply to a file the same way they apply to the console.
* **Always check that a file opened.** `if (!stream)` catches a missing file or a permission problem, instead of letting the program carry on with nothing.
* **A read loop stops at the end of the file.** `while (std::getline(in, line))` runs while lines remain.
* **Closing flushes and releases the file.** A file closes at `close()`, or when its stream goes out of scope.
* **`std::fstream` keeps existing contents.** Writing a shorter text over a longer file leaves the leftover text behind. Use `std::ofstream`, or the `std::ios::trunc` flag, to replace the whole file.

### Check your understanding

*These questions are written for this course.*

````quiz
Which class should you use to replace the entire contents of a file?
○ std::ifstream
→ Not quite. ifstream reads a file, and can't write to it.
◉ std::ofstream
→ Yes. An ofstream clears the file when it opens, so the new text replaces everything.
○ std::fstream, with no other options
→ Not quite. It keeps the old contents, so leftover text can remain.
````

````quiz
A file read loop `while (std::getline(in, line))` stops when what happens?
○ The first empty line is read.
→ Not quite. An empty line is a line, and the loop continues past it.
◉ There are no more lines to read, so getline returns false.
→ Yes. The loop condition is false once the end of the file is reached.
○ The file is closed by the loop.
→ Not quite. The loop reads, and the file stays open until it's closed.
````

````quiz
Why check `if (!in)` after opening a file for reading?
○ Because reading always fails the first time.
→ Not quite. Reading works when the file opens.
◉ So that a missing file is reported, rather than silently appearing empty.
→ Yes. A stream that didn't open gives no lines, which looks like an empty file.
○ To move the reading position to the start.
→ Not quite. Checking a stream doesn't change where it reads from.
````
