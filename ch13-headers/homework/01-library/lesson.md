## Homework: Library

Write a small library program split across files: a `Book` class in its own header and source, a `Library` class in its own header and source, and a `main.cpp` that uses them.

The program should:

* in `Book.h` and `Book.cpp`, define a class `Book` with a constructor that takes a title, a `print` method that prints `Dune - available` or `Dune - checked out`, and a `checkOut` method that marks the book as checked out
* in `Library.h` and `Library.cpp`, define a class `Library` that holds up to three books in a private array, with an `add` method that stores a `const Book&` if there's room, and a `printAll` method that prints every book it holds
* use include guards in both headers, and no `using namespace` line in either header
* in `main.cpp`, create a library, create the books `Dune` and `Emma`, check out `Emma` before adding it to the library, and call `printAll`. `add` stores a copy, so a checkout made after adding doesn't reach the library's copy.

### What to check

The output should be:

```
Dune - available
Emma - checked out
```

Check the file list in the step's CMake file. Every `.cpp` file the program uses must appear in `add_executable`, or the link fails.

### Extensions

* Make `add` refuse a fourth book, and print a message when the library is full. Decide whether the message belongs in `add` or in `main`, and say why.
* Add a `count` method to `Library` that returns the number of books, and print it after the books are added.

---

*This exercise is not from the book. It practices the ideas in Chapter 13.*
