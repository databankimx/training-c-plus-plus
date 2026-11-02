## Input

This step waits for you to type a line. Press **Run**. The Output pane shows the prompt:

```
What is your name?
```

Type a name in the input box at the bottom of the Output pane, and press Enter. The program then prints a greeting, and finishes:

```
Hello, Ada!
```

While the program is waiting, **Stop (Esc)** ends it. Try pressing Run, then Stop, to see that the run ends and the Run button comes back.

---

### Try it in the runner

Delete the `std::flush` in `src/main.cpp` and run again. Output sent to a pipe is buffered, so the prompt may not appear until after you type a name. Put `std::flush` back to fix it.
