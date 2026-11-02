## Stack traces

When a program fails deep inside a call, the error message tells you what went wrong, but not how the program got there. A stack trace is the list of functions that were running at that moment, from the innermost call out to `main`. It answers the question "who called this?", which is often the first thing you need to know.

Here's the core of the program from `src/main.cpp`. The innermost function captures its own stack:

```cpp
void inner() {
    std::stacktrace trace = std::stacktrace::current();
    std::cout << "Frames captured: " << (trace.size() > 0 ? "yes" : "no") << "\n";
    throw std::runtime_error("inner failed");
}
```

`std::stacktrace::current()` returns the call stack as it stands at that line. The `<stacktrace>` header provides it, and the program links the `stdc++exp` library in this step's CMake file, since the standard library needs it for stack traces. The `size` of the trace is the number of frames it holds.

Press **Run**. The output is:

```
Frames captured: yes
Caught: inner failed
```

The trace was captured inside `inner`, and then the exception carried the program back to the `catch` in `main`. Each function between them, `middle` and `main`, sat on the stack when the trace was taken.

### Reading a trace

Each frame in the trace has a description, which names the function and the source location when the program was built with debug information. The "Try" asks you to print these descriptions, from the innermost frame outward. The names read as a list of who called whom: `inner`, then `middle`, then `main`, with some frames from the standard library's startup code after them.

### The Backtrace checkbox

The Output header has a Backtrace checkbox. When it's on, the runner builds with `-g`, which adds debug information, so the frame descriptions show function names and line numbers. With it off, the program still captures frames, but the names can be missing. Turn it on when you're diagnosing a problem, and leave it off for timing or output checks, since the debug build runs more slowly.

### The cost

Capturing a stack trace takes time, and the trace holds memory. A program shouldn't capture one on every call, or in a loop that runs millions of times. Capture it where an error is reported, or where a failure is unexpected, and keep it out of normal control flow.

---

### Quiz

*These questions are written for this course.*

````quiz
What does a stack trace show?
○ The values of every variable in the program.
→ Not quite. A stack trace shows the functions that are running, not their variables.
◉ The chain of function calls that led to the current point, from the innermost call out to main.
→ Yes. It answers the question of who called this.
○ The lines of code that were never reached.
→ Not quite. A stack trace shows the calls that are in progress.
````

````quiz
Why should a program avoid capturing a stack trace on every call?
○ Because stack traces can only be captured once.
→ Not quite. A trace can be captured any number of times.
◉ Because capturing a trace takes time and memory, which adds up in code that runs often.
→ Yes. Capture it where an error is reported, not in the normal path of the program.
○ Because the trace would replace the program's output.
→ Not quite. The trace is separate from the output unless the program prints it.
````

---

### Try it in the runner

Add a loop that prints `trace[i].description()` for each frame in `trace`, and predict the first name before you press **Run**. The first frame is `inner`, since that's where the trace was captured. Then turn on the Backtrace checkbox and run again, and compare the names with the checkbox off.

---

A stack trace turns a failure into a path through the program, and the Backtrace option makes the path readable. The next step covers assertions, which check conditions that should always hold.
