## Booleans and comparisons

Every program makes decisions. It checks whether a value is big enough, whether a name was entered, or whether two things match, and then it chooses what to do next. The data type for those decisions is `bool`, which holds one of two values: `true` or `false`.

Here's the program for this step, in `src/main.cpp`. It begins with two `bool` variables, printed in two ways:

```cpp
bool is_coding_fun = true;
bool is_fish_tasty = false;

std::cout << "Without boolalpha:\n";
std::cout << "is_coding_fun: " << is_coding_fun << "\n";
std::cout << "is_fish_tasty: " << is_fish_tasty << "\n";
```

Press **Run**. The output is:

```
Without boolalpha:
is_coding_fun: 1
is_fish_tasty: 0
```

By default, C++ prints `true` as `1` and `false` as `0`. That's how the language has always worked, and you'll see it in older code. The next part of the program changes it:

```cpp
std::cout << std::boolalpha;
```

`std::boolalpha` is a setting for the output stream, so everything printed from now on shows `true` and `false`. The output becomes:

```
With boolalpha:
is_coding_fun: true
is_fish_tasty: false
```

The setting stays on until you turn it off with `std::noboolalpha`. Set it once, near the top of your output, and every bool after it prints as words.

### Comparisons

A comparison asks a question about two values, and the answer is a `bool`. The operators are:

| Operator | Meaning | Example | Result |
|---|---|---|---|
| `==` | Equal to | `x == 10` | `true` |
| `!=` | Not equal to | `x != y` | `true` |
| `>` | Greater than | `x > y` | `true` |
| `<` | Less than | `x < y` | `false` |
| `>=` | Greater than or equal to | `x >= 10` | `true` |
| `<=` | Less than or equal to | `y <= 8` | `false` |

With `x` as 10 and `y` as 9, the results in the table are what the program prints.

Notice that equality is `==`, with two equals signs, and not `=`. A single `=` is assignment, which you've been using since the variables lesson. Writing `if (x = 10)` assigns 10 to `x`, and then tests whether 10 is true, which is almost never what you meant. Most compilers warn you about it, so keep the warnings on.

### Comparing types

You can compare `int` values with each other, and `double` values with each other. Mixing them works as well, because the `int` is converted to a `double` for the comparison. That's the same promotion you saw in arithmetic, and it's the one place where an `int` and a `double` can meet without any conversion on your part.

Comparing text is a different matter, and it's covered when we return to strings later in the course.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `std::boolalpha` change?
○ It makes the program run faster.
→ Not quite. It only changes how bool values are printed.
◉ It makes bool values print as true and false, rather than 1 and 0.
→ Yes. The setting applies to everything printed afterwards.
○ It stops bool values from being printed at all.
→ Not quite. The values still print, just as words instead of numbers.
````

````quiz
Which expression is true when `x` is 10?
○ x = 9
→ Not quite. That assigns 9 to x, and it doesn't ask a question at all.
◉ x == 10
→ Yes. == asks whether x is equal to 10.
○ x != 10
→ Not quite. That's true only when x is not 10.
````

---

### Try it in the runner

Change `y` to `10`, and press **Run**. Before you do, predict the values of `x == y` and `x < y`. Both `x` and `y` will be 10, so `x == y` becomes `true` and `x < y` becomes `false`.

Then add a line to the output that reads `std::cout << "x = 3: " << (x = 3) << "\n";`, and press **Run**. The program still builds, because `x = 3` is a valid assignment, and it changes `x` to 3, so any line that uses `x` afterwards sees the new value. Writing `=` where you meant `==` is a common mistake, and it's the one to watch for when you read code.

---

Booleans are the raw material of every decision a program makes. The next step combines them, so one condition can depend on two others.
