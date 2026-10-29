## Reference parameters

The parameters in this chapter so far have each received a copy of the caller's value. Changing a copy inside the function leaves the caller's variable alone. That's the right behavior most of the time, but some jobs need to change the caller's variables, and a swap is the classic example. A reference parameter gives the function access to the caller's variable itself.

Here's the program for this step, in `src/main.cpp`:

```cpp
void swapNums(int& x, int& y) {
    int z = x;
    x = y;
    y = z;
}
```

The `&` after `int` in each parameter makes it a reference, as the references step described. Each name inside the function is another name for the caller's variable. Assigning to `x` assigns to `firstNum`, and assigning to `y` assigns to `secondNum`.

Press **Run**. The output is:

```
10 20
20 10
```

The first line is printed before the call, and the second after it. The swap ran on the variables `main` owns, so their values have changed.

### Copy or reference

Compare this with the earlier parameters. In `introduce(std::string fname, int age)`, the function receives copies, so changing `age` inside it would have no effect outside. The `&` is the only difference between a parameter that copies and one that refers to the caller's variable.

Choose the copy by default. It keeps the function from changing things it wasn't asked to change, and it makes the function's effect easier to see from its call. Use a reference when the job is to change the caller's variable, or when the value is large and copying it would be wasteful. You'll see the second case with `const` in later chapters.

### Why a swap needs references

If you remove the `&` from both parameters, the function still runs, and the swap happens inside it. But the swap is then done on copies, and `main` prints the original values again. That's a bug that compiles without any warning, which is why the reference matters. Check what a function changes, and what it's meant to change.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the swap need reference parameters?
○ Because references make the swap faster.
→ Not quite. The reason is what the function can change, not speed.
◉ Because the function must change the caller's variables, not copies of them.
→ Yes. A reference gives the function access to the caller's variables.
○ Because the swap won't compile with ordinary parameters.
→ Not quite. It compiles, but the caller would see no change.
````

````quiz
What does a reference parameter do that an ordinary parameter doesn't?
○ It makes the argument a constant.
→ Not quite. A reference doesn't change whether the argument can be changed.
◉ It refers to the caller's variable, so changes made in the function are visible to the caller.
→ Yes. The name inside the function is another name for the caller's variable.
○ It holds a copy that is cleared when the function returns.
→ Not quite. That describes an ordinary parameter.
````

---

### Try it in the runner

Remove the `&` from both parameters, and press **Run**. Predict the second line of output before you do. The swap happens on copies, so the line shows 10 20 again, which is the same as before the call. Put the `&` back, and check that the swap works again.

---

Reference parameters let a function change its caller's variables, and the default parameters from earlier still copy. The next step is recursion, a function that calls itself.
