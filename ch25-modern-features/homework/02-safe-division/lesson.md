## Homework: Safe division

Division by zero has no answer, so a function that divides should say so, rather than crash or return a magic value. In this exercise, you write a division that returns an `std::optional<int>`, and print each result, handling the empty case.

The program should:

* write `std::optional<int> safeDivide(int a, int b)`, which returns the quotient when `b` isn't zero, and `std::nullopt` when it is
* in `main`, call `safeDivide(10, 2)` and print `10 / 2 = ` followed by the result, using `value()` only after checking the optional
* call `safeDivide(1, 0)` and print `1 / 0 = no answer` when the result is empty
* print the result for `safeDivide(9, 3)` in the same form as the first call

### What to check

The output should be:

```
10 / 2 = 5
1 / 0 = no answer
9 / 3 = 3
```

The check comes before any use of the value. Using `value()` on an empty optional throws an exception, which the program doesn't catch in this exercise, so the check is what keeps it running.

### Extensions

* Change the output for the empty case to use `value_or` with a fallback, and explain why that version prints the fallback in place of the words "no answer".
* Write the same function with an exception instead of an optional. Explain which version a caller would find easier to get right, and why.

---

*This exercise is not from the book. It practices the ideas in Chapter 25, with the exceptions from Chapter 9.*
