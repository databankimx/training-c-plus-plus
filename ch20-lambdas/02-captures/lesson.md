## Captures

A lambda often needs a value from the code around it. The square brackets at the start of the lambda say how it gets that value. This is called the capture list, and it decides whether the lambda holds its own copy of a variable, or refers to the original.

The program has two lambdas with different captures.

```cpp
int factor = 3;
auto scaleByCopy = [factor](int x) { return x * factor; };
factor = 10;
std::cout << "Scaled by copy: " << scaleByCopy(5) << "\n";
```

`[factor]` captures a copy of `factor` at the moment the lambda is created. The change to `factor` afterward doesn't reach the lambda, so the lambda still multiplies by 3. The output is `Scaled by copy: 15`.

```cpp
int total = 0;
auto addTo = [&total](int x) { total += x; };
addTo(4);
addTo(6);
std::cout << "Total by reference: " << total << "\n";
```

`[&total]` captures a reference to `total`. The ampersand means the lambda uses the original variable, so each call changes it. After both calls, `total` is 10, and the output is `Total by reference: 10`.

Press **Run**. The output for the whole program is:

```
Scaled by copy: 15
Total by reference: 10
```

### Copy or reference

Capture by copy when the lambda should see the value as it was, and capture by reference when it should change or see the current value of the original. The same choice appears with function parameters in the functions chapter: a copy is the default, and a reference is used when the change must reach the caller.

A lambda that keeps a reference to a local variable must not outlive that variable. If you store the lambda and call it after the function that owns `total` has returned, the reference refers to a variable that no longer exists. That's undefined behavior, and a bug that's hard to spot.

### Capture everything

Two shorthand forms exist. `[=]` captures every variable the lambda uses by copy, and `[&]` captures them all by reference. They're convenient for short lambdas, but they hide which variables the lambda depends on. Naming each capture, as this step does, makes the dependency visible in the code.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `scaleByCopy` still multiply by 3 after `factor` is changed to 10?
○ Because the lambda was compiled before the change.
→ Not quite. The timing of compilation doesn't matter here.
◉ Because `[factor]` captured a copy of the value at the time the lambda was created.
→ Yes. The lambda holds its own copy, which the later change doesn't reach.
○ Because lambdas can't use variables from the code around them.
→ Not quite. They can, through the capture list.
````

````quiz
What is the danger in storing a lambda that captures a local variable by reference?
○ The lambda becomes slower.
→ Not quite. Speed is not the issue.
◉ If the lambda is called after the variable is gone, it refers to memory that no longer exists.
→ Yes. Calling it then is undefined behavior.
○ The lambda can't be stored in a variable.
→ Not quite. It can be stored, but the stored lambda must not outlive the variables it refers to.
````

---

### Try it in the runner

Change the capture of `scaleByCopy` from `[factor]` to `[&factor]`, and predict the value it prints before you press **Run**. The lambda now refers to `factor`, which is 10 when the call happens, so the output is `Scaled by copy: 50`. The name still says "copy", so the name should change as well, and the lesson's point is that the capture decides the behavior.

---

A capture decides whether a lambda holds a copy of a variable or refers to the original. The next step is the chapter summary, and then two homework exercises that use lambdas with the standard algorithms.
