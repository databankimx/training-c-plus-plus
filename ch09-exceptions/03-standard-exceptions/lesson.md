## Standard exceptions

The earlier steps threw an `int`. That works, but the value says nothing about what went wrong beyond its number. The standard library provides exception classes that carry a message, and they're the usual choice for errors in C++ code.

Here's the program for this step, in `src/main.cpp`. The division function refuses a zero divisor by throwing a standard exception:

```cpp
int safeDivide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("the divisor must not be zero");
    }
    return a / b;
}
```

`std::invalid_argument` comes from the `<stdexcept>` header. Its constructor takes a message, which is stored in the exception object. The message describes the problem, so whoever catches the error can report it without knowing the function's internals.

Press **Run**. The output is:

```
10 / 2 = 5
Error: the divisor must not be zero
```

The first division succeeds, and prints its result. The second throws. The line `10 / 0 = ...` never prints, because the value of `second` is never produced.

### Catching by reference

The catch block is written as:

```cpp
} catch (const std::exception& error) {
    std::cout << "Error: " << error.what() << "\n";
}
```

The `const std::exception&` is a reference, as the references chapter described, so the catch refers to the exception object without copying it. `error.what()` returns the message. `std::exception` is the base class of all the standard exception types, so this one catch handles any of them.

### The standard exception classes

Several classes derive from `std::exception`, and each one names a category of problem:

| Class | Use it for |
|---|---|
| `std::invalid_argument` | A value passed to a function is unacceptable |
| `std::out_of_range` | An index or value is outside its valid range |
| `std::logic_error` | A mistake in the program's logic, which the program could have prevented |
| `std::runtime_error` | A problem that only shows up while the program runs, such as a failed read |

Choose the class that describes the problem, and give it a message that helps the reader. A catch can then match a whole family of errors through `std::exception`, or a single class when the handling differs.

### Why not catch(...)

`catch (...)` catches any exception, whatever its type. It has no name for the value, so it can't report a message, and it can hide errors you didn't mean to catch. Use it only at the outermost level of a program, where the choice is to report the failure and stop. Otherwise, name the type you expect.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the program print `Error:` and never `10 / 0 = ...`?
○ Because the message is printed before the division.
→ Not quite. The division happens first, and then the message is printed.
◉ Because the throw stops the function, so `second` is never set and the line never runs.
→ Yes. The throw leaves the try block before the output line can run.
○ Because std::cout can't print after an exception.
→ Not quite. Output works normally, and the program simply skips the line.
````

````quiz
Which class is the best fit for a function that receives an index beyond the end of its data?
○ std::invalid_argument
→ Possibly, but a range problem is more exactly described by a different class.
◉ std::out_of_range
→ Yes. The class names the problem: a value outside its valid range.
○ std::runtime_error
→ Not quite. That describes problems found only while running, rather than a range error.
````

---

### Try it in the runner

Change the catch to `catch (...)`, and replace its body with a fixed message such as `std::cout << "Error\n";`. Press **Run**. The message is no longer available, so the output says only that an error occurred, with no text describing it. Then change it back, since a message is the reason for choosing a standard exception.

Then remove the try block entirely, and keep the call to `safeDivide(10, 0)`. Press **Run**. The exception is not caught, so the program stops with a message, and its exit code shows the termination. This is the same outcome as the earlier step's mismatched catch.

---

Standard exceptions give an error a type and a message, and a `catch` can name the type it expects. The summary and homework put these together with the file errors from the last chapter.
