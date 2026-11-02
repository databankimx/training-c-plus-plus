## Homework: Ownership handoff

In this exercise, you hand a resource to a function by moving it, and watch the function become its owner until it returns.

The program should:

* define a `Resource` class whose constructor prints `Acquire <name>` and whose destructor prints `Release <name>`
* define `consume(std::unique_ptr<Resource> resource)`, which takes its `unique_ptr` by value, and prints `Received <name>`. The name can be taken from a member function, or the function can print a fixed message that names the resource
* in `main`, create a `std::unique_ptr<Resource>` for a resource named `handoff`, pass it to `consume` with `std::move`, and then print `Back in main`
* print `End` before `main` returns

### What to check

The output should be:

```
Acquire handoff
Received handoff
Release handoff
Back in main
End
```

The `Release` line comes before `Back in main`. The function owned the resource while it ran, and it released it when it returned, since nothing kept the object alive after that. Predict the output before you run it, and explain why `Release handoff` appears where it does.

### Extensions

* Change `consume` to take a `const std::unique_ptr<Resource>&` instead. Predict whether the release still happens inside `consume`, and check your prediction.
* Remove the `std::move` from the call, and read the compiler's error. Explain why the compiler refuses it.

---

*This exercise is not from the book. It practices the ideas in Chapter 18, with the smart pointers from Chapter 17.*
