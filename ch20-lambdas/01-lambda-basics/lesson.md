## Lambda basics

A function you need once, in one place, is awkward to declare separately. A lambda is an unnamed function written where it's used. It's the feature that lets code say "here is the rule" directly in a call, and it's the usual way to customize the standard library.

Here's the simplest lambda from `src/main.cpp`:

```cpp
auto square = [](int x) { return x * x; };
std::cout << "Square of 4: " << square(4) << "\n";
```

The square brackets start the lambda. They hold the captures, which are covered in the next step, and here they're empty. The parentheses hold the parameters, and the braces hold the body, exactly as they do for a function. The lambda is stored in a variable named `square`, using `auto`, so the compiler works out its type. You call it like any function, and the output is `Square of 4: 16`.

### A lambda as a comparison

The standard sort takes an optional third argument, the comparison that decides whether one value should come before another. By default it's `<`. A lambda can replace it:

```cpp
std::sort(values.begin(), values.end(), [](int a, int b) { return a > b; });
```

The lambda returns true when `a` should come before `b`. Using `>` puts the largest values first, so the list is sorted from largest to smallest. Press **Run**, and the output is:

```
Descending: 9 6 5 4 3 2 1 1
```

This is the rule the standard library step mentioned. The sort's steps are still inside the library, but the rule that defines the order now comes from the code that calls it.

### The comparison must be a strict order

A comparison used for sorting must say that a value is not before itself, and that if `a` is before `b`, then `b` is not before `a`. `a < b` and `a > b` both meet that rule. A comparison such as `a <= b` doesn't, and the sort can misbehave, because equal values seem to come before each other. Use `<` or `>` in a sort.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `[](int a, int b) { return a > b; }` return when it's called?
○ The larger of the two values.
→ Not quite. It returns true or false, not a value.
◉ true when a should come before b in the order being sorted, and false otherwise.
→ Yes. The sort uses that answer to decide the order.
○ The difference between a and b.
→ Not quite. A comparison answers yes or no, not a number.
````

````quiz
Which comparison produces an ascending sort?
○ a > b
→ Not quite. That puts the largest values first.
◉ a < b
→ Yes. A value comes before another when it's smaller.
○ a == b
→ Not quite. Equality doesn't order values, and it can't sort a list.
````

---

### Try it in the runner

Change the comparison to `a < b`, and predict the order of the output before you press **Run**. The list is sorted from smallest to largest: 1 1 2 3 4 5 6 9.

---

A lambda is a function written where it's needed, and a comparison lambda gives the standard sort a rule. The next step covers captures, which let a lambda use the variables around it.
