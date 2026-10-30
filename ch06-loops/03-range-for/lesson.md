## Range-based for loops

Many loops don't count at all. They go through every value in an array, one after another, and the counter would only get in the way. C++ has a loop for that: the range-based `for`, which reads almost like English. It's the usual way to visit each element of an array.

Here's the program for this step, in `src/main.cpp`. It starts with an array of integers:

```cpp
int scores[] = {10, 20, 30, 40, 50};
std::cout << "Scores:\n";
for (int score : scores) {
    std::cout << score << "\n";
}
```

Press **Run**. The output is:

```
Scores:
10
20
30
40
50
```

Read `for (int score : scores)` as "for each score in scores". The variable `score` takes each element of the array in turn, and the body runs once for each one. There's no counter to start, check, or step, and no index to get wrong. Compare this with the array chapter's approach of writing out each element, and the advantage is clear.

The program then does the same with an array of strings:

```cpp
std::string colors[] = {"red", "green", "blue"};
for (std::string color : colors) {
    std::cout << color << "\n";
}
```

The output is `red`, `green`, and `blue`, each on its own line. Here `color` is a `std::string`, so it holds any text. Each element is copied into `color` before the body runs.

### When to use the other loops

The range-based `for` is the usual choice when you want to look at every element, and you don't need to know the position of each one. Use a `for` loop with a counter when you need the index, or when you want to skip some elements, or stop early, or visit only part of the array. The `for` loop from the last step handles those, because it gives you the counter as well as the value.

### Copying each value

The loop variable is a copy of each element. Changing `score` inside the loop doesn't change the array. To change the elements themselves, the loop variable has to be a reference, which a later chapter covers.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `for (int n : values)` do when `values` holds five integers?
○ Counts from 0 to 4.
→ Not quite. The loop visits the elements, and it doesn't count indexes.
◉ Runs the body once for each element, in order, with n set to each value in turn.
→ Yes. The variable n takes each element in turn.
○ Runs the body five times, with n set to 0 to 4.
→ Not quite. n holds the element values, not their positions.
````

````quiz
Which loop is the better choice when you need the index of each element?
○ The range-based for, since it always gives the index.
→ Not quite. The range-based form gives the values, and doesn't provide an index.
◉ A for loop with a counter.
→ Yes. The counter gives you the index directly.
○ A while loop with no counter.
→ Not quite. Without a counter, the loop has no index to report.
````

---

### Try it in the runner

Add `"yellow"` to the `colors` array, and press **Run**. Predict whether the loop needs any other change. It doesn't: the array's size is worked out from the list, and the loop visits every element, including the new one.

Then change `"green"` to `"orange"` in the `colors` array, and predict the second block of output. The loop visits each element in order, so the output is `red`, `orange`, and `blue`.

---

The range-based `for` says what you mean, with no counter to get wrong. The next step covers the two statements that change how any loop runs: `break` and `continue`.
