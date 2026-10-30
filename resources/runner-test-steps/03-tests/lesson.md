## Tests

This step has two programs. The program adds two numbers and prints the sum. The tests check the function that does the adding.

Press **Test**. The Output pane shows the build, and then the test results:

```
All tests passed
```

Then open `tests/test_math.cpp` from the file selector above the Source pane. It has the checks. Each check either passes or prints a line that says what failed.

---

### Try it in the runner

Change `add` in `src/math.hpp` so it returns the wrong answer, and press **Test**. The Output pane shows the failed check, and the test run reports a failure. Put the function back to test again.
