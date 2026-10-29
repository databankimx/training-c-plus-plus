## Homework: Counter

Write a class that counts, with a constructor that sets a starting value.

The class should:

* have a constructor that takes a starting count, and stores it in a private member
* have an `increment` method that adds one to the count
* have a `reset` method that sets the count back to zero
* have a `value` method that returns the count, and is declared `const`

In `main`:

* create a counter with `Counter c;`, which needs a constructor that works with no arguments, so the count starts at zero
* call `increment` three times, then print `Count: 3`
* call `reset`, then print `Count: 0`
* create a second counter starting at 10, call `increment` once, and print `Count: 11`

### What to check

The output should be:

```
Count: 3
Count: 0
Count: 11
```

The first line depends on the three calls, and the second on `reset` returning the count to zero. The last shows that the starting value is used.

### Extensions

* Add a `decrement` method that refuses to go below zero, and print a message when it's called at zero.
* Add a second constructor that takes no arguments, and check that it's the same as the default constructor you wrote. Think about whether two constructors are needed, or whether one can serve both.

---

*This exercise is not from the book. It practices the ideas in Chapter 11.*
