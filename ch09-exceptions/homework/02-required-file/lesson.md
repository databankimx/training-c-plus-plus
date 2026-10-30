## Homework: Required file

Write a program that reads a file the program needs. If the file can't be opened, the reading function throws an exception, and `main` reports the problem.

The program should:

* define `printFile`, which takes a file name as a `std::string`, opens the file, and throws a `std::runtime_error` with the message `could not open <name>` when it can't
* print each line of the file when it opens, using `std::getline`
* in `main`, call `printFile` on `data/settings.txt` inside a `try` block, and print the file's lines
* catch the exception, and print its message with `what()`

The file `data/settings.txt` is already in the step's `data` folder.

### What to check

Run the program as it is. The two lines of the settings file should appear, and no error should be reported.

Then change the file name to `data/missing.txt`, and run again. The output should be `could not open data/missing.txt`, and the program should end normally.

### Extensions

* Use `std::invalid_argument` instead of `std::runtime_error` for an empty file name, and check the name before opening it. Decide whether an empty name is a mistake in the program, or a problem with the data. That decides the class.
* Call `printFile` for two files, one after the other, so that a failure in the first doesn't stop the second. Think about where the `try` block has to go.

---

*This exercise is not from the book. It practices the ideas in Chapter 9, and it uses the file reading from Chapter 8.*
