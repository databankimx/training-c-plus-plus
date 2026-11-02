## Homework: Guarded section

A guard is a small object whose destructor undoes something when the scope ends. In this exercise, you'll write a guard and check that its destructor still runs when an exception leaves the function early.

The program should:

* define a class `Guard` whose constructor takes a name and prints `Enter <name>`, and whose destructor prints `Leave <name>`
* define `process(bool fail)`, which creates a `Guard` named `section`, prints `Working`, throws a `std::runtime_error` with the message `work failed` when `fail` is true, and otherwise prints `Finished working`
* in `main`, call `process(false)` and then `process(true)` inside a `try` block, and catch the exception as a `const std::exception&`, printing `Caught: ` followed by its message
* print `End` after the `try` block

### What to check

The output should be:

```
Enter section
Working
Finished working
Leave section
Enter section
Working
Leave section
Caught: work failed
End
```

The line `Leave section` in the second call comes before `Caught`. That's the point of the exercise: the guard's destructor runs while the exception travels out of the function, before the `catch` that handles it.

### Extensions

* Add a second `Guard` to `process`, and predict the order of the two `Leave` messages when the exception is thrown. Check your prediction.
* Remove the `try` block from `main`, and describe what the program does when the exception isn't caught. Note whether the guard's destructor still runs first.

---

*This exercise is not from the book. It practices the ideas in Chapter 17, with the exceptions from Chapter 9.*
