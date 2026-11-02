## Homework: Shared owners

In this exercise, several owners share one resource, and you watch the owner count change as they're added and removed.

The program should:

* define a `Resource` class whose constructor prints `Acquire <name>` and whose destructor prints `Release <name>`
* in `main`, create a `std::shared_ptr<Resource>` named `original` for a resource called `shared`
* create a `std::vector<std::shared_ptr<Resource>>` named `holders`
* add `original` to `holders` with `push_back`, and print `Owners: ` followed by `original.use_count()`
* add `original` to `holders` a second time, and print the owner count again
* clear `holders` with `clear()`, and print the owner count again
* print `End`, then let `main` return

### What to check

The output should be:

```
Acquire shared
Owners: 2
Owners: 3
Owners: 1
End
Release shared
```

The first owner count is 2, not 1, because `original` and the first copy in `holders` both own the resource. Explain why `Release shared` comes after `End`, not before. Then explain what would change if `original.reset()` were called before `clear()`.

### Extensions

* Create a second resource, and show that its owner count is independent of the first.
* Explain why `use_count` should not decide the logic of a program that has threads.

---

*This exercise is not from the book. It practices the ideas in Chapter 17.*
