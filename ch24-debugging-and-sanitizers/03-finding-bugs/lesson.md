## Finding bugs

Reading code carefully finds many bugs, but some hide in plain sight. A program runs without a crash, produces a number, and the number is wrong. A debugger lets you stop the program partway through, look at its variables, and move forward one step at a time, so you can see the moment the values stop making sense.

This step is a bug hunt. The program sums the numbers from 1 to 10, and it prints the wrong answer:

```
Sum of 1 to 10: 45
```

The answer should be 55, since the sum of 1 through 10 includes 10 itself. Nothing crashes and no message appears, so the only way to find the fault is to watch the program run.

### Setting up the debugger

The runner can't stop a program partway through, so this step is done in VS Code, with the C/C++ extension installed. Open the step's `src/main.cpp` in VS Code, in the step's folder in the repository, `ch24-debugging-and-sanitizers\03-finding-bugs`, and debug from there.

1. Click in the left margin next to the line `total += i;` to set a breakpoint. A red dot appears.
2. Press **F5**, or choose **Run and Debug** and then **C/C++: g++ build and debug active file**. If VS Code asks for a configuration, choose the one for the step's program.
3. The program stops at the breakpoint. The **Variables** panel shows `total` and `i`.

Use **Step Over** (F10) to run one loop pass at a time, and watch `total` and `i` change. Use **Continue** (F5) to run to the next breakpoint.

### What to look for

Step through the loop and write down the value of `i` on each pass. Then compare the last value of `i` with the number you want to add up to. The loop condition `i < n` stops one step too early for an inclusive sum. The fault is in the condition, not in the addition.

A bug like this is called an off-by-one error, and it's one of the most common mistakes in loops. The boundaries of a loop are the first places to check when a total or a count is off by one.

### Debugging habits

* **Reproduce first.** The bug must happen every time, with input you can write down.
* **Check the assumption, not the code.** Decide what should be true at a point, then check it with a breakpoint or an assertion.
* **Change one thing at a time.** A change that fixes a bug and changes something else makes the result harder to trust.

---

### Quiz

*These questions are written for this course.*

````quiz
What is the usual way to find a bug like this one, where the output is wrong but nothing fails?
○ Guess which line is wrong, and change it.
→ Not quite. A guess can waste time, and it can hide the real fault.
◉ Stop the program at a breakpoint, watch the variables, and step forward until the values stop making sense.
→ Yes. The debugger shows the exact point where the program departs from what it should do.
○ Add more output to the program, and read the numbers.
→ Not quite. Printing can help, but a debugger shows the same values without changing the program.
````

````quiz
What is an off-by-one error?
○ An error that stops the program with an exception.
→ Not quite. That describes a different kind of failure.
◉ A mistake in a loop boundary that makes the loop run one time too few or too many.
→ Yes. The boundary condition is the usual place to look.
○ A mistake in the order of two statements.
→ Not quite. That's an ordering error, not an off-by-one.
````

---

### Try it in the runner

Predict the final value of `i` when the loop ends, for `n` equal to 10. It's 10, since the loop stops when `i` reaches 10 and doesn't run for it. Then change the loop condition so that `i` includes 10, and predict the output. It's 55.

---

A debugger lets you watch a program's values one step at a time, so a wrong answer can be traced to its cause. The next step is sanitizers, which find some of the same mistakes automatically, when the toolchain supports them.
