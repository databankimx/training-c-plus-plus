## Homework: Move through a vector

A `std::vector` of `unique_ptr` values is a common way to keep a list of owned objects. In this exercise, you move one resource into a vector, and then move it back out.

The program should:

* define a `Resource` class whose constructor prints `Acquire <name>` and whose destructor prints `Release <name>`
* in `main`, create a `std::unique_ptr<Resource>` named `p` for a resource called `vessel`
* create a `std::vector<std::unique_ptr<Resource>>` named `holders`
* move `p` into `holders` with `push_back(std::move(p))`, and print `Size after push: ` followed by `holders.size()`
* print `p owns nothing: yes` if `p` is empty, and `p owns nothing: no` otherwise
* move the first element back out into a new `std::unique_ptr<Resource>` named `back`, using `std::move(holders[0])`
* call `holders.pop_back()`, which removes the now-empty element
* print `Got back: yes` if `back` owns the resource, and `Got back: no` otherwise
* print `End`, then let `main` return

### What to check

The output should be:

```
Acquire vessel
Size after push: 1
p owns nothing: yes
Got back: yes
End
Release vessel
```

Notice that `pop_back` prints nothing. The element it removes is empty, so there's no resource to release, and the release happens only when `back` goes out of scope at the end of `main`.

### Extensions

* Move two resources into the vector, and check the size. Explain why the order of their release is not something to depend on in this exercise.
* Remove the `std::move` from the `push_back` call, and explain the compiler error.

---

*This exercise is not from the book. It practices the ideas in Chapter 18, with the containers from Chapter 14.*
