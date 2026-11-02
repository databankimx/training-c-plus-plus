## Summary: Decisions

This chapter covered how a program chooses what to do, based on the values it has.

* **`bool` holds true or false.** `std::boolalpha` makes it print as words rather than 1 and 0.
* **Comparisons ask questions.** `==`, `!=`, `<`, `>`, `<=`, and `>=` each give a bool. Equality is `==`, and a single `=` assigns a value instead.
* **Logical operators combine bools.** `&&` needs both sides to be true, `||` needs one, and `!` flips a value. XOR is true when exactly one side is true, and C++ can express it with `p != q`, or with `(p || q) && !(p && q)`.
* **Precedence sets the reading order.** `!` binds most tightly, then the comparisons, then `&&`, then `||`. Add parentheses when mixing `&&` and `||`, and the compiler's warning will not appear.
* **Short-circuit evaluation stops early.** `&&` and `||` skip the right side when the left side already decides the answer. Put the safe check first.
* **`if` runs a block on a condition.** `else` runs when the condition is false, and `else if` tests further conditions in order. The first true branch wins. The final `else` is optional.
* **Chain or separate `if` blocks.** A chain runs only one block, so use it when the conditions exclude each other. When several conditions can apply, and each should run, use separate `if` blocks.
* **The conditional operator chooses a value.** `condition ? a : b` gives `a` when the condition is true, and `b` otherwise.
* **`switch` picks a case by value.** Use it when one value is compared with several constants. Each case ends with `break`, unless `[[fallthrough]]` marks the drop-through as deliberate. A `switch` works on integers and `char`, not on strings.
* **Always use braces.** They stop a later edit from putting a line outside the `if` by accident.

### Check your understanding

*These questions are written for this course.*

````quiz
What does `std::boolalpha` change about how bool values print?
○ Nothing, bool values always print as numbers.
→ Not quite. It changes how they print, and it's the reason true and false appear as words.
◉ It prints true and false, rather than 1 and 0.
→ Yes. The setting stays on until you turn it off with std::noboolalpha.
○ It converts them to strings.
→ Not quite. They're still bool values, and they print as words only.
````

````quiz
Which expression is true when `age` is 15 and `has_permission` is true?
○ age >= 18 && has_permission
→ Not quite. 15 is not 18 or over, so the left side is false.
◉ age < 18 || has_permission
→ Yes. Either side being true is enough for ||, and has_permission is true.
○ age == 15 && !has_permission
→ Not quite. That needs has_permission to be false, and it's true here.
````

````quiz
What is the value of `result` after `int result = (5 > 3) ? 10 : 20;`?
○ 20
→ Not quite. 20 is the value used when the condition is false, and 5 is greater than 3.
◉ 10
→ Yes. The condition is true, so the first value, 10, is used.
○ true
→ Not quite. The conditional operator gives one of its two values, not the condition itself.
````
