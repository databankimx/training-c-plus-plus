## Arithmetic

Most programs spend a lot of their time doing sums, so C++ gives you the usual arithmetic operators. Here they are, with the examples from this step's program. The table shows `a` as 7 and `b` as 2:

| Operator | Meaning | Example | Result |
|---|---|---|---|
| `+` | Addition | `a + b` | 9 |
| `-` | Subtraction | `a - b` | 5 |
| `*` | Multiplication | `a * b` | 14 |
| `/` | Division (whole numbers when both sides are `int`) | `a / b` | 3 |
| `%` | Remainder after integer division (integers only) | `a % b` | 1 |

They work the way you'd expect from school, with one important exception that catches almost everyone at least once. This lesson covers the operators, that exception, and how to print decimal numbers neatly.

Here's the program for this step, in `src/main.cpp`:

```cpp
int a = 7;
int b = 2;

std::cout << "a + b = " << a + b << "\n";
std::cout << "a - b = " << a - b << "\n";
std::cout << "a * b = " << a * b << "\n";
std::cout << "a / b = " << a / b << "\n";
std::cout << "a % b = " << a % b << "\n";
```

Press **Run**. The first lines of output are:

```
a + b = 9
a - b = 5
a * b = 14
a / b = 3
a % b = 1
```

Five of the operators are here. `+`, `-`, and `*` do what you'd expect. `/` is division, and `%` is the remainder operator, which gives what's left over after dividing. Seven divided by two is three with one left over, so `a % b` is 1.

### The division trap

Look at `a / b` again. Seven divided by two is three and a half, but the output says 3. That's not a mistake in the compiler. When both numbers are `int`, C++ does whole-number division, and it throws away the fraction. The answer is always rounded down towards zero.

That matters more than it first appears. The unit converter in the homework divides by 5, and if you write it as `9 / 5` with whole numbers, every answer comes out wrong. The fix is to make at least one of the numbers a decimal.

The next lines of the program show that:

```cpp
double c = 7.0;
std::cout << "c / b = " << c / b << "\n";
std::cout << "a / 2.0 = " << a / 2.0 << "\n";
```

The output is:

```
c / b = 3.5
a / 2.0 = 3.5
```

When one side of an operator is a `double`, the whole calculation is done in decimals. `2.0` is a decimal literal, and `a` is promoted to a decimal before the division. Either way, you get 3.5.

### Converting on purpose

Sometimes both values are `int`, and you still want a decimal answer. Then you convert one of them explicitly:

```cpp
double average = static_cast<double>(a) / b;
```

`static_cast<double>(a)` turns `a` into a decimal for this calculation, and the division happens in decimals. The variable `a` itself stays an `int`. The conversion lasts only for the expression.

`static_cast` is the safe, clear way to convert in C++. You'll see older code that uses `(double)a`, and that still works, but the `static_cast` form tells the reader exactly what you intended.

### Order of operations

When a calculation has more than one operator, C++ doesn't simply work left to right. It follows precedence rules, which decide which operation happens first. They match the rules you learned at school:

| Order | Operators | Rule |
|---|---|---|
| First | `( )` | Parentheses are worked out first, so you can use them to force the order you want. |
| Second | `*`, `/`, `%` | Multiplication, division, and remainder, from left to right. |
| Third | `+`, `-` | Addition and subtraction, from left to right. |

The program prints three lines that show all three rules:

```
2 + 3 * 4 = 14
(2 + 3) * 4 = 20
10 - 4 - 3 = 3
```

`2 + 3 * 4` is 14, not 20. The multiplication happens first, so it's `2 + 12`. Parentheses change that: `(2 + 3) * 4` adds first, so it's `5 * 4`, which is 20.

The last line shows the left-to-right rule. `10 - 4 - 3` is worked out as `(10 - 4) - 3`, which is 3. Operators at the same level are done in the order they're written, from left to right.

When you're not sure, use parentheses. They cost nothing, and they make the order obvious to the next reader.

### Combined operators

Combined operators are worth knowing, because you'll use them constantly. Each one does an arithmetic operation and stores the result back in the same variable:

| Operator | Meaning | Example | Same as |
|---|---|---|---|
| `++` | Add one | `count++` | `count = count + 1` |
| `--` | Subtract one | `count--` | `count = count - 1` |
| `+=` | Add | `total += 5` | `total = total + 5` |
| `-=` | Subtract | `total -= 3` | `total = total - 3` |
| `*=` | Multiply | `total *= 2` | `total = total * 2` |
| `/=` | Divide | `total /= 4` | `total = total / 4` |
| `%=` | Remainder | `total %= 4` | `total = total % 4` |

> **Before or after?** `++` and `--` can go in front of a variable or after it, and the two positions behave differently when the value is used inside a larger expression.
>
> In `count++`, the variable is increased after its current value has been used. In `++count`, the variable is increased first, and the new value is used.
>
> ```cpp
> int x = 5;
> int a = x++;   // a is 5, then x becomes 6
> int b = ++x;   // x becomes 7, then b is 7
> ```
>
> When `++` or `--` is a statement on its own, as in every example in this lesson, the two forms do exactly the same thing. The difference only shows up when the result is used. That's why many style guides suggest using the form that reads most clearly, and keeping `++` and `--` out of longer expressions until you're comfortable with the difference.

The program uses several of these on the same variable, starting from 10. Each line changes `total` a little more:

```cpp
int total = 10;
total -= 3;   // 7
total *= 2;   // 14
total /= 4;   // 3, because int division drops the fraction
total %= 4;   // 3
```

The `total /= 4` step is the division trap from earlier in this lesson. Because `total` is an `int`, the result is 3, not 3.5, and the rest of the sequence works from that 3.

The right-hand side is always worked out first. So `total *= 2 + 3` means `total = total * (2 + 3)`, which multiplies by 5, not by 2 and then adds 3. The same precedence rules apply inside a combined operator as anywhere else.

You'll meet `+=` on text too. In the strings lesson, `greeting += " Welcome."` adds text to the end of a string, in the same way `total += 5` adds to a number. The operator does the same job for both, because a string's `+` joins text in the same way a number's `+` adds.

The first two lines of the program use `count++` and `count += 5` the same way, and that's why `count` ends at 6.

### Printing decimals neatly

A decimal can print with far more digits than you want. The program switches the output into a fixed format with two places after the point:

```cpp
std::cout << std::fixed << std::setprecision(2);
std::cout << "average to two places = " << average << "\n";
```

The output is `average to two places = 3.50`. The `std::setprecision` manipulator comes from `<iomanip>`, which is why the program includes it. Once set, the format stays on for every decimal after it, so the setting is usually made once, near the top of the output.

### Math functions

The standard library has ready-made functions for the calculations you'd otherwise have to work out by hand. The last lines of the program use some of them:

| Function | Header | Returns | Example | Result |
|---|---|---|---|---|
| `std::max(a, b)` | `<algorithm>` | The larger of two values | `std::max(7, 2)` | 7 |
| `std::min(a, b)` | `<algorithm>` | The smaller of two values | `std::min(7, 2)` | 2 |
| `std::sqrt(x)` | `<cmath>` | The square root of `x` | `std::sqrt(16.0)` | 4 |
| `std::pow(x, y)` | `<cmath>` | `x` raised to the power `y` | `std::pow(2.0, 10)` | 1024 |
| `std::round(x)` | `<cmath>` | `x` rounded to the nearest whole number | `std::round(2.6)` | 3 |
| `std::floor(x)` | `<cmath>` | `x` rounded down | `std::floor(2.6)` | 2 |
| `std::ceil(x)` | `<cmath>` | `x` rounded up | `std::ceil(2.1)` | 3 |

The output of the program shows these lines:

```
max(a, b) = 7
min(a, b) = 2
sqrt(16) = 4.00
round(2.6) = 3.00
pow(2, 10) = 1024.00
```

`max` and `min` come from `<algorithm>`, and the rest come from `<cmath>`. Each function takes values and returns a result, which you can print or store, like any other expression. You'll write your own functions later, in the functions chapter, and they're used in exactly the same way.

The decimal results print with two places, because `std::fixed` and `std::setprecision(2)` are still set from earlier in the program. The `max` and `min` lines print whole numbers, because `a` and `b` are integers. Try the same calls on decimals, and you'll see the formatting setting apply to them as well.

`std::round` and `std::floor` both give whole numbers, but as `double` values. If you need an `int`, convert the result with `static_cast<int>`, the same way you converted a number for division.

### A note on decimals

A `double` can't store every decimal exactly. Some values, such as 0.1, are stored as the closest binary fraction, which is very close but not exact. That's why a calculation that should give 0.3 may print as something like 0.30000000000000004 if you ask for enough digits. For everyday output, `setprecision` hides the difference. For money or other exact values, you'd use a different approach, which a later chapter covers.

---

### Quiz

*These questions are written for this course.*

````quiz
What is the value of `7 / 2` when both numbers are `int`?
○ 3.5
→ Not quite. With two whole numbers, C++ divides in whole numbers and drops the fraction.
◉ 3
→ Yes. The fraction is dropped, so the answer is rounded down to 3.
○ 4
→ Not quite. Integer division rounds towards zero, so it doesn't round up here.
````

````quiz
Which expression gives a decimal answer of 3.5 for `a` equal to 7?
○ a / 2
→ Not quite. Both values are whole numbers, so the fraction is lost.
◉ a / 2.0
→ Yes. The 2.0 is a decimal, so the division is done in decimals.
○ a % 2
→ Not quite. % gives the remainder, which is 1 here.
````

````quiz
What is the value of `2 + 3 * 4`?
○ 20
→ Not quite. Reading strictly left to right would give (2 + 3) * 4, which is 20. Multiplication comes first.
◉ 14
→ Yes. The multiplication happens first, giving 2 + 12.
○ 24
→ Not quite. That would mean multiplying the 2 as well, which the rules don't do.
````

````quiz
After `int x = 10;` and then `x /= 4;`, what is `x`?
○ 2.5
→ Not quite. x is an int, so it can't hold a fraction.
◉ 2
→ Yes. 10 divided by 4 is 2 with the fraction dropped.
○ 3
→ Not quite. Integer division drops the fraction rather than rounding, so 2.5 becomes 2, not 3.
````

---

### Try it in the runner

Change `b` to `4`, and press **Run**. Before you do, predict the values of `a / b` and `a % b`. Seven divided by four is one with three left over, so `a / b` should be 1 and `a % b` should be 3.

Then change `a / 2.0` to `a / 2`. The value drops from 3.5 to 3, because both sides are whole numbers again. Finally, change `10 - 4 - 3` to `10 - (4 - 3)`, and predict the answer. The parentheses change the order, so the answer is 9, not 3. Last, predict the value of `total` after `total *= 2 + 3`, starting from `total` at 1. The answer is 5, because the right-hand side is worked out first.

---

Arithmetic is where the numbers in your variables start to do something. The next step introduces strings, the other kind of value you'll meet in almost every program.
