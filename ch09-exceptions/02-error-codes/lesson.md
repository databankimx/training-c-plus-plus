## Error codes

The last step threw an `int` that was the age itself. Often the value thrown is a code that says what went wrong, and the catch block chooses a message from it. This step uses that approach, with a `switch` from the decisions chapter to pick the message.

Here's the program for this step, in `src/main.cpp`. The function throws a different code for each kind of failure:

```cpp
void checkAccess(int age) {
    if (age < 18) {
        throw -1;
    }
    if (age >= 65) {
        throw -2;
    }
    std::cout << "Access granted.\n";
}
```

Press **Run**, and enter `15` at the prompt. The output is:

```
Enter your age: 15
Access denied! Underage!
```

The age is under 18, so the function throws `-1`. The `catch (int err)` receives it as `err`, and the `switch` on `err` picks the message for that code. Enter `40`, and the function returns normally, printing `Access granted.` Enter `70`, and it throws `-2`, which the switch turns into `Access denied! Too old!`.

### The boundary

The range the function accepts is 18 up to, but not including, 65. An age of exactly 65 is refused, so the check is `age >= 65`, not `age > 65`. Testing the boundary values is the best way to catch an off-by-one error in a condition like this, and the Try asks you to do exactly that.

### The limit of codes

Error codes work, but they say little. A reader sees `-2` and has to look up what it means, and nothing stops a different function from throwing `-2` for an unrelated reason. The `catch (int err)` can't tell the difference. Codes also collide with ordinary `int` values, so a program can't always tell an error from a normal result.

The next step uses thrown objects from the standard library, which carry a message and a type that describe what failed.

### Input errors

If the user types a word instead of a number, `std::cin` fails, and `age` stays at 0. Zero is under 18, so the program reports the user as underage. That's wrong, but it's the same input problem the Battleship program handled. This step doesn't handle it, and the homework does.

---

### Quiz

*These questions are written for this course.*

````quiz
An age of exactly 65 is refused. Which condition in the function produces that?
○ age > 65
→ Not quite. That refuses only ages above 65, so 65 would pass.
◉ age >= 65
→ Yes. The range accepted is 18 up to, but not including, 65.
○ age == 65
→ Not quite. That would refuse only the one age, and ages above 65 would pass.
````

````quiz
What is the main weakness of using error codes such as -2?
○ They make the program run more slowly.
→ Not quite. The cost of a code is negligible.
◉ A reader has to look up what each code means, and unrelated errors can share a code.
→ Yes. A code says little about the failure, and two causes can use the same number.
○ They can't be caught by a catch block.
→ Not quite. They are caught, as the example shows.
````

---

### Try it in the runner

Enter `65` at the prompt, and predict the message. It's `Access denied! Too old!`. Then enter `64`, and predict again. It's `Access granted.`

Then enter `abc`, and predict the message. You might expect an error, but the input fails, `age` stays 0, and the program prints `Access denied! Underage!`. That's the input problem from the lesson, which the homework addresses.

---

A thrown code tells the catch block what went wrong, and a `switch` turns it into a message. The next step replaces raw codes with standard exception objects, which carry a description of the failure with them.
