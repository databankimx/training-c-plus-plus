## Throwing values

A program often reaches a point where it can't carry on normally. A value is missing, a number is out of range, or a file won't open. The usual tool for that is an exception: the code throws a value, the normal flow stops at once, and control passes to a `catch` block that deals with the problem.

Here's the program for this step, in `src/main.cpp`. The function refuses an age below 18 by throwing it:

```cpp
void checkAccess(int age) {
    if (age < 18) {
        throw age;
    }
    std::cout << "Access granted - you are old enough.\n";
}
```

The `throw` statement takes a value, here an `int`, and sends it out of the function. Nothing after the `throw` runs, and the call in `main` doesn't return normally.

The code that calls the function sits inside a `try` block, and a `catch` block follows it:

```cpp
try {
    checkAccess(25);
    checkAccess(15);
    std::cout << "This line never runs.\n";
} catch (int myNum) {
    std::cout << "Access denied - you must be at least 18 years old.\n";
    std::cout << "Age is: " << myNum << "\n";
}
```

Press **Run**. The output is:

```
Access granted - you are old enough.
Access denied - you must be at least 18 years old.
Age is: 15
```

The first call passes, and prints its message. The second call throws 15. Control leaves `checkAccess` immediately, skips the line that says `This line never runs.`, and jumps to the `catch` block. The `catch (int myNum)` matches a thrown `int`, and `myNum` receives the value that was thrown, 15.

### Why use this instead of a return value

A function can report failure by returning a special value, such as -1. That works for simple cases, but the caller has to check every call, and a forgotten check lets the bad value carry on. An exception can't be ignored in the same way. If nothing catches it, the program stops with a message, rather than continuing with a wrong answer.

Exceptions also cross function boundaries. The `throw` happened inside `checkAccess`, but the `catch` sits in `main`. You don't need to pass the error back through every function in between, and the functions in between don't need to know about it.

### Only matching catches handle a throw

The `catch` names a type, and it handles only values of that type. A thrown `int` is caught by `catch (int ...)`, but not by `catch (double ...)`. The next step uses a `catch` that can see the thrown value itself, and the step after that shows a catch that accepts any type.

---

### Quiz

*These questions are written for this course.*

````quiz
When `throw` runs inside a function, what happens to the rest of that function?
○ It runs, and then the throw takes effect.
→ Not quite. The throw ends the function at once.
◉ It doesn't run, and control passes to the matching catch.
→ Yes. Nothing after the throw runs, and the search for a catch begins.
○ It runs only if the value thrown is an int.
→ Not quite. Whatever the type, the rest of the function is skipped.
````

````quiz
In the example, which catch block handles a thrown `int`?
○ catch (double value)
→ Not quite. A catch only matches values of its own type.
◉ catch (int myNum)
→ Yes. The type matches, and myNum receives the value thrown.
○ There isn't one, so the program continues.
→ Not quite. Without a matching catch, the exception is not handled, and the program stops.
````

---

### Try it in the runner

Change `checkAccess(15)` to `checkAccess(30)`, and predict whether the catch block runs and which lines print. Both calls now pass, so there's no throw. The output is the granted message twice, followed by `This line never runs.`, since the try block finishes normally.

Then change the catch type to `double`, and press **Run**. The `int` isn't matched, so nothing handles it. The program stops with an error message, and the exit code shows that it terminated. Change the catch back to `int` before you continue.

---

A `throw` sends a value out of the normal flow, to the nearest `catch` of the same type. The next step uses thrown values to report several kinds of error, and it handles each one in its own way.
